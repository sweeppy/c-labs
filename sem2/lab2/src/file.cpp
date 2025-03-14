#include "file.hpp"
#include <cstdio>
#include "colors.hpp"

using std::cout;
using std::endl;

BaseFile::BaseFile() : file(nullptr) {}

BaseFile::BaseFile(const char *path, const char *mode)
{
    file = fopen(path, mode);
    if (!file)
    {
        throw std::runtime_error("Error in constructor. Failed to open file");
    }
}

BaseFile::BaseFile(FILE *f) : file(f)
{
    if (!file)
    {
        throw std::runtime_error("Error in constructor. Failed to open file");
    }
}

BaseFile::~BaseFile()
{
    if (file)
    {
        cout << YELLOW << "File destructor called for object: " << this << RESET << endl;
        fclose(file);
        file = nullptr;
    }
}

bool BaseFile::is_open() const
{
    return file != nullptr;
}

bool BaseFile::can_read() const
{
    if (!file)
        return false;
    int c = std::fgetc(file);
    if (c == EOF)
        return false;
    std::ungetc(c, file); // refresh reader position
    return true;
}

bool BaseFile::can_write() const
{
    if (!file)
        return false;
    if (std::fputc(0, file) == EOF)
        return false;
    std::fseek(file, -1, SEEK_CUR); // refresh writer position
    return true;
}

size_t BaseFile::write_raw(const void *buf, size_t n_bytes)
{
    if (!file)
        throw std::runtime_error("File is not open");
    return fwrite(buf, 1, n_bytes, file);
}

size_t BaseFile::read_raw(void *buf, size_t max_bytes)
{
    if (!file)
        throw std::runtime_error("File is not open");
    return fread(buf, 1, max_bytes, file);
}

long BaseFile::tell()
{
    if (!file)
        throw std::runtime_error("File is not open");
    return ftell(file);
}

bool BaseFile::seek(long offset)
{
    if (!file)
        throw std::runtime_error("File is not open");
    return fseek(file, offset, SEEK_SET) == 0;
}

size_t BaseFile::write(const void *buf, size_t n_bytes)
{
    return write_raw(buf, n_bytes);
}

size_t BaseFile::read(void *buf, size_t max_bytes)
{
    return read_raw(buf, max_bytes);
}

// BASE 32 FILE

Base32File::Base32File(const char *path, const char *mode, const char *customTable)
    : BaseFile(path, mode), table(customTable)
{
    if (strlen(table) != 32)
    {
        throw std::invalid_argument("Table must contain exactly 32 characters");
    }
}

size_t Base32File::write(const void *buf, size_t n_bytes)
{
    size_t size = encoded32_size(n_bytes);
    char *encodedData = new char[size];
    if (encode32(static_cast<const char *>(buf), n_bytes, encodedData) != 0)
    {
        delete[] encodedData;
        throw std::runtime_error("Failed to encode data");
    }
    // Write encoded data in file
    size_t result = BaseFile::write_raw(encodedData, size);
    delete[] encodedData;
    return result;
}

size_t Base32File::read(void *buf, size_t max_bytes)
{
    size_t encodedSize = encoded32_size(max_bytes);
    char *encodedData = new char[encodedSize];
    size_t readSize = BaseFile::read_raw(encodedData, encodedSize);

    char *decodedData = static_cast<char *>(buf);
    if (decode32(encodedData, readSize, decodedData) != 0)
    {
        delete[] encodedData;
        throw std::runtime_error("Failed to decode data");
    }

    delete[] encodedData;
    return decoded32_size(readSize);
}

size_t Base32File::encoded32_size(int raw_size)
{
    return (raw_size * 8 + 4) / 5;
}
size_t Base32File::decoded32_size(int encode_size)
{
    return (encode_size * 5) / 8;
}

int Base32File::encode32(const char *raw_data, int raw_size, char *dst)
{
    if (!raw_data || !dst || raw_size <= 0)
        return 1;

    int bit_pos = 0;
    int dst_pos = 0;
    int current_value = 0; // здесь число от 0 до 31 (5 бит)

    for (int i = 0; i < raw_size; i++)
    {
        for (int bit = 7; bit >= 0; bit--)
        {
            int bit_value = (raw_data[i] >> bit) & 1; // Получение значения бита

            current_value = (current_value << 1) | bit_value; // Добавление значение бита в число из 5 бит;

            bit_pos++;

            // Если считался 5-ый бит
            if (bit_pos == 5)
            {
                dst[dst_pos++] = table[current_value];
                bit_pos = 0;
                current_value = 0;
            }
        }
    }

    if (bit_pos > 0) // Если остались незакодированные биты(дополнение нулями)
    {
        current_value = current_value << (5 - bit_pos);
        dst[dst_pos] = table[current_value];
    }
    return 0;
}

int Base32File::decode32(const char *encoded_data, int encoded_size, char *dst)
{
    if (!encoded_data || !dst || encoded_size <= 0)
        return 1;

    int bit_pos = 0;
    int dst_pos = 0;
    int current_value = 0;

    for (int i = 0; i < encoded_size; i++)
    {
        int code_number = -1; // Число закодированное в символ (от 0 до 31)
        for (int j = 0; j < 32; j++)
        {
            if (table[j] == encoded_data[i])
            {
                code_number = j;
                break;
            }
        }
        if (code_number == -1)
            return 2;

        for (int bit = 4; bit >= 0; bit--)
        {
            int bit_value = (code_number >> bit) & 1;

            current_value = (current_value << 1) | bit_value;

            bit_pos++;

            if (bit_pos == 8)
            {
                dst[dst_pos++] = current_value;
                current_value = 0;
                bit_pos = 0;
            }
        }
    }

    if (bit_pos > 0) // Если остались не раскодированные биты
    {
        current_value <<= 8 - bit_pos;
        dst[dst_pos] = current_value;
    }

    return 0;
}

// RLE FILE

RleFile::RleFile(const char *path, const char *mode) : BaseFile(path, mode) {}

size_t RleFile::write(const void *buf, size_t n_bytes)
{
    size_t output_size;
    const char *encodedData = encode(static_cast<const char *>(buf), n_bytes, output_size);

    size_t result = BaseFile::write_raw(encodedData, output_size);
    delete[] encodedData;
    return result;
}

// size_t RleFile::read(void *buf, size_t max_bytes)
// {
//     return size_t();
// }

char *RleFile::encode(const char *data, size_t data_size, size_t &output_size)
{
    if (!data || data_size == 0)
    {
        output_size = 0;
        return nullptr;
    }
    char *dst = new char[data_size * 2];
    size_t dst_pos = 0;
    size_t data_pos = 0;

    while (data_pos < data_size)
    {
        char current_symbol = data[data_pos];
        int count = 1;

        // Is next symbol repeatable
        bool is_repeatable = (data_pos + 1 < data_size) && (data[data_pos + 1] == current_symbol);

        if (is_repeatable)
        {
            while (data_pos + count < data_size && data[data_pos + count] == current_symbol && count <= 127)
            {
                count++;
            }

            // Encode repeatable symbols
            dst[dst_pos++] = static_cast<char>(count); // count
            dst[dst_pos++] = current_symbol;           // symbol
            data_pos += count;
        }
        else
        {
            int non_repeat_count = 0;
            while (data_pos + non_repeat_count < data_size &&
                   (non_repeat_count == 0 || data[data_pos + non_repeat_count] != data[data_pos + non_repeat_count - 1]) &&
                   non_repeat_count <= 127)
            {
                non_repeat_count++; // count of non-repeatable symbols in a row
            }

            dst[dst_pos++] = static_cast<char>(-non_repeat_count); // the number below zero before symbols
            for (int i = 0; i < non_repeat_count; i++)
            {
                dst[dst_pos++] = data[data_pos++]; // symbols
            }
        }
    }
    output_size = dst_pos;
    return dst;
}

// int RleFile::decode(const char *data, size_t data_size, const char *dst)
// {
//     return 0;
// }
