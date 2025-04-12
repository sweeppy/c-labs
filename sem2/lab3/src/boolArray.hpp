#include <iostream>

class BoolArray
{
private:
    struct BitsField
    {
        char b0 : 1, b1 : 1, b2 : 1, b3 : 1, b4 : 1, b5 : 1, b6 : 1, b7 : 1;
    };

    union Byte
    {
        BitsField bits;
        char value;

        Byte() : value(0) {}
        Byte(bool val) : value(val ? 0xFF : 0x00) {}
    };

    Byte *data;
    size_t size_;

    bool get_bit(size_t pos) const;
    void set_bit(size_t pos, bool val);

public:
    BoolArray() = delete;
    BoolArray(size_t size, bool value = false);

    ~BoolArray();

    BoolArray(const BoolArray &other);

    BoolArray &operator=(const BoolArray &other);

    class BitHelper
    {
    private:
        BoolArray &arr;
        size_t pos;

    public:
        BitHelper(BoolArray &array, size_t pos) : arr(array), pos(pos) {}

        BitHelper(const BitHelper &) = delete;

        BitHelper &operator=(bool value);
        BitHelper &operator=(const BitHelper &other);

        operator bool() const;
    };

    BitHelper operator[](size_t pos);

    bool operator[](size_t pos) const;

    size_t size() const;

    void resize(size_t new_size, bool value = false);
};