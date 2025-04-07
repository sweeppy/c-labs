#include <iostream>
#define INLINE_CAPACITY (sizeof(short(*)) + 2 * sizeof(size_t)) / sizeof(short)

class ShortArray
{
private:
    union
    {
        struct
        {
            short data[INLINE_CAPACITY];
            size_t count;
        } stack;
        struct
        {
            short *data;
            size_t current_capacity;
            size_t count;
        } heap;
    } storage;

    bool is_on_heap() const;

    void ensure_capacity(size_t required_capacity);

public:
    ShortArray();
    ShortArray(size_t initial_capacity, short fill_value = 0);

    ~ShortArray();

    ShortArray(const ShortArray &other);
    ShortArray(ShortArray &&moved);

    ShortArray &operator=(const ShortArray &other);
    ShortArray &operator=(ShortArray &&moved);

    short &operator[](size_t index);

    void push(short new_val);
    short pop();
    size_t size() const;
    void resize(size_t new_size, short fill_value = 0);
};