#include "boolArray.hpp"

bool BoolArray::get_bit(size_t pos) const
{
    if (pos >= size_)
        throw std::out_of_range("Index out of range");

    size_t byte_index = pos / 8;
    size_t bit_index = pos % 8;

    switch (bit_index)
    {
    case 0:
        return data[byte_index].bits.b0;
        break;
    case 1:
        return data[byte_index].bits.b1;
        break;
    case 2:
        return data[byte_index].bits.b2;
        break;
    case 3:
        return data[byte_index].bits.b3;
        break;
    case 4:
        return data[byte_index].bits.b4;
        break;
    case 5:
        return data[byte_index].bits.b5;
        break;
    case 6:
        return data[byte_index].bits.b6;
        break;
    case 7:
        return data[byte_index].bits.b7;
        break;

    default:
        throw std::logic_error("Invalid index");
        break;
    }
}

void BoolArray::set_bit(size_t pos, bool val)
{
    if (pos >= size_)
        throw std::out_of_range("Index out of range");

    size_t byte_index = pos / 8;
    size_t bit_index = pos % 8;

    switch (bit_index)
    {
    case 0:
        data[byte_index].bits.b0 = val;
        break;
    case 1:
        data[byte_index].bits.b1 = val;
        break;
    case 2:
        data[byte_index].bits.b2 = val;
        break;
    case 3:
        data[byte_index].bits.b3 = val;
        break;
    case 4:
        data[byte_index].bits.b4 = val;
        break;
    case 5:
        data[byte_index].bits.b5 = val;
        break;
    case 6:
        data[byte_index].bits.b6 = val;
        break;
    case 7:
        data[byte_index].bits.b7 = val;
        break;

    default:
        throw std::logic_error("Invalid index");
        break;
    }
}

BoolArray::BoolArray(size_t size, bool value) : size_(size)
{
    size_t bytes = (size_ + 7) / 8;
    data = new Byte[bytes];

    Byte fill(value);
    for (size_t i = 0; i < bytes; i++)
    {
        data[i] = fill;
    }
}

BoolArray::~BoolArray()
{
    delete[] data;
}

BoolArray::BoolArray(const BoolArray &other) : size_(other.size_)
{
    size_t bytes = (size_ + 7) / 8;
    data = new Byte[bytes];

    for (size_t i = 0; i < bytes; i++)
    {
        data[i].value = other.data[i].value;
    }
}

BoolArray &BoolArray::operator=(const BoolArray &other)
{
    if (this != &other)
    {
        delete[] data;
        size_ = other.size_;

        size_t bytes = (size_ + 7) / 8;
        data = new Byte[bytes];

        for (size_t i = 0; i < bytes; i++)
        {
            data[i].value = other.data[i].value;
        }
    }
    return *this;
}

BoolArray::BitHelper &BoolArray::BitHelper::operator=(bool value)
{
    arr.set_bit(pos, value);
    return *this;
}

BoolArray::BitHelper &BoolArray::BitHelper::operator=(const BitHelper &other)
{
    bool val = other.arr.get_bit(other.pos);
    arr.set_bit(pos, val);
    return *this;
}

BoolArray::BitHelper::operator bool() const
{
    return arr.get_bit(pos);
}

BoolArray::BitHelper BoolArray::operator[](size_t pos)
{
    return BitHelper(*this, pos);
}

bool BoolArray::operator[](size_t pos) const
{
    return get_bit(pos);
}

size_t BoolArray::size() const
{
    return size_;
}

void BoolArray::resize(size_t new_size, bool value)
{
    if (new_size == size_)
        return;

    size_t old_bytes = (size_ + 7) / 8;
    size_t new_bytes = (new_size + 7) / 8;

    Byte *new_data = new Byte[new_bytes];
    Byte fill;
    fill.value = value ? 0xFF : 0x00;

    size_t copy_bytes = old_bytes < new_bytes ? old_bytes : new_bytes;
    for (size_t i = 0; i < copy_bytes; ++i)
    {
        new_data[i].value = data[i].value;
    }

    for (size_t i = old_bytes; i < new_bytes; ++i)
    {
        new_data[i] = fill;
    }

    if (new_size > size_ && new_size % 8 != 0)
    {
        size_t last_bit_pos = new_size % 8;
        uint8_t mask = (1 << last_bit_pos) - 1;

        if (value)
        {
            new_data[new_bytes - 1].value |= mask;
        }
        else
        {
            new_data[new_bytes - 1].value &= ~mask;
        }
    }

    delete[] data;
    data = new_data;
    size_ = new_size;
}