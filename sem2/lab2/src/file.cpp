#include "file.hpp"
#include "colors.hpp"
#include "coder.hpp"

using std::cout;
using std::endl;

BaseFile::BaseFile() : file(nullptr)
{
    std::cout << BLUE << "BaseFile default constructor called for object: " << this
              << RESET << std::endl;
}

BaseFile::BaseFile(const char *path, const char *mode)
{
    file = fopen(path, mode);
    if (!file)
    {
        throw std::runtime_error("Error in constructor. Failed to open file");
    }
    std::cout << BLUE
              << "BaseFile parameterized constructor (with path and mode) called for object: "
              << this << RESET << std::endl;
}

BaseFile::BaseFile(FILE *f) : file(f)
{
    if (!file)
    {
        throw std::runtime_error("Error in constructor. Failed to open file");
    }
    std::cout << BLUE
              << "BaseFile parameterized constructor (with *FILE) called for object: "
              << this << RESET << std::endl;
}

BaseFile::~BaseFile()
{
    if (file)
    {
        fclose(file);
        file = nullptr;
    }
    std::cout << YELLOW << "BaseFile destructor called for object: " << this << RESET << std::endl;
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

Base32File::Base32File() : BaseFile()
{
    std::cout << BLUE
              << "Base32File default constructor called for object: "
              << this << RESET << std::endl;
}

Base32File::Base32File(const char *path, const char *mode, const char *customTable)
    : BaseFile(path, mode), table(customTable)
{
    if (strlen(table) != 32)
    {
        throw std::invalid_argument("Table must contain exactly 32 characters");
    }
    std::cout << BLUE
              << "Base32File parameterized constructor called for object: "
              << this << RESET << std::endl;
}
Base32File::~Base32File()
{
    std::cout << YELLOW << "Base32File destructor called for object: " << this
              << RESET << std::endl;
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
    return _encoded32_size(raw_size);
}
size_t Base32File::decoded32_size(int encode_size)
{
    return _decoded32_size(encode_size);
}

int Base32File::encode32(const char *raw_data, int raw_size, char *dst)
{
    return _encode32(raw_data, raw_size, dst, table);
}

int Base32File::decode32(const char *encoded_data, int encoded_size, char *dst)
{
    return _decode32(encoded_data, encoded_size, dst, table);
}

// RLE FILE

RleFile::RleFile(const char *path, const char *mode) : BaseFile(path, mode)
{
    std::cout << BLUE
              << "RleFile parameterized constructor called for object: "
              << this << RESET << std::endl;
}

RleFile::~RleFile()
{
    std::cout << YELLOW << "RleFile destructor called for object: " << this
              << RESET << std::endl;
}

size_t RleFile::write(const void *buf, size_t n_bytes)
{
    size_t output_size;
    const char *encodedData = encodeRLE(static_cast<const char *>(buf), n_bytes, output_size);
    size_t result = BaseFile::write_raw(encodedData, output_size);
    delete[] encodedData;
    return result;
}

size_t RleFile::read(void *buf, size_t max_bytes)
{
    char *encodedData = new char[max_bytes];
    size_t readSize = BaseFile::read_raw(encodedData, max_bytes);

    char *decodedData = static_cast<char *>(buf);
    if (decodeRLE(encodedData, readSize, decodedData) != 0)
    {
        delete[] encodedData;
        throw std::runtime_error("Failed to decode data");
    }

    delete[] encodedData;
    return readSize;
}

char *RleFile::encodeRLE(const char *data, size_t data_size, size_t &output_size)
{
    return _encodeRLE(data, data_size, output_size);
}

int RleFile::decodeRLE(const char *data, size_t data_size, char *dst)
{
    return _decodeRLE(data, data_size, dst);
}

// Non classes function

void write_int(IFile &file, int n)
{

    if (n < 0 && n != 0)
    {
        file.write("-", 1);
        n = -n;
    }

    int count = (n == 0) ? 1 : 0;
    for (int temp = n; temp > 0; temp /= 10)
    {
        count++;
    }

    while (n > 0)
    {
        int first_number = static_cast<int>(n / std::pow(10, count - 1));
        char digit = static_cast<char>(first_number + '0');
        file.write(&digit, 1);
        n = n - first_number * static_cast<int>(std::pow(10, count - 1));
        count--;
    }
}
