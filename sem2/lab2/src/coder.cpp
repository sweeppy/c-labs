#include "coder.hpp"

size_t _encoded32_size(int raw_size)
{
    return (raw_size * 8 + 4) / 5;
}

size_t _decoded32_size(int encode_size)
{
    return (encode_size * 5) / 8;
}

int _encode32(const char *raw_data, int raw_size, char *dst, const char *table)
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
int _decode32(const char *encoded_data, int encoded_size, char *dst, const char *table)
{
    if (!encoded_data || !dst || encoded_size <= 0)
    {
        return 1;
    }

    int bit_pos = 0;
    int dst_pos = 0;
    int current_value = 0;

    for (int i = 0; i < encoded_size; i++)
    {
        int code_number = 0; // Число закодированное в символ (от 0 до 31)
        for (int j = 0; j < 32; j++)
        {
            if (table[j] == encoded_data[i])
            {
                code_number = j;
                break;
            }
        }

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

char *_encodeRLE(const char *data, size_t data_size, size_t &output_size)
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
            int non_repeat_count = 2;

            while (data_pos + non_repeat_count < data_size &&
                   (data[data_pos + non_repeat_count] != data[data_pos + non_repeat_count - 1]) &&
                   (data[data_pos + non_repeat_count + 1] != data[data_pos + non_repeat_count]) &&
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

int _decodeRLE(const char *data, size_t data_size, char *dst)
{
    if (!data || data_size == 0)
    {
        return 1;
    }

    size_t data_pos = 0;
    size_t dst_pos = 0;

    while (data_pos < data_size)
    {
        char count_symbol = data[data_pos++];
        size_t now_count = std::abs(static_cast<int>(count_symbol));

        if (static_cast<int>(count_symbol) > 0) // repeatable symbols in a row
        {
            if (data_pos >= data_size)
            {
                return 2;
            }

            char symbol = data[data_pos++];
            for (size_t i = 0; i < now_count; i++)
            {
                dst[dst_pos++] = symbol;
            }
        }
        else // unrepeatable symbols in a row
        {
            if (data_pos + now_count > data_size)
            {
                return 3;
            }

            for (size_t i = 0; i < now_count; i++)
            {
                dst[dst_pos++] = data[data_pos++];
            }
        }
    }

    return 0;
}
