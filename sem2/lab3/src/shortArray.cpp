#include "shortArray.hpp"

bool ShortArray::is_on_heap() const
{
    return storage.heap.count > INLINE_CAPACITY;
}
// * private:
void ShortArray::ensure_capacity(size_t required_capacity)
{
    if (is_on_heap())
    {
        if (storage.heap.current_capacity >= required_capacity || required_capacity <= 0)
            return;

        size_t new_capacity = std::max(storage.heap.current_capacity * 2, required_capacity);

        short *new_data = new short[new_capacity];
        for (size_t i = 0; i < storage.heap.count; i++)
        {
            new_data[i] = storage.heap.data[i];
        }
        delete[] storage.heap.data;
        storage.heap.data = new_data;
        storage.heap.current_capacity = new_capacity;
    }
    else
    {
        if (required_capacity < INLINE_CAPACITY)
            return;

        short *new_data = new short[required_capacity];
        for (size_t i = 0; i < storage.stack.count; i++)
        {
            new_data[i] = storage.stack.data[i];
        }
        storage.heap.data = new_data;
        storage.heap.count = storage.stack.count;
        storage.heap.current_capacity = required_capacity;
    }
}

// * public:

ShortArray::ShortArray()
{
    storage.stack.count = 0;
}

ShortArray::ShortArray(size_t initial_capacity, short fill_value)
{
    if (initial_capacity <= INLINE_CAPACITY)
    {
        for (size_t i = 0; i < initial_capacity; i++)
        {
            storage.stack.data[i] = fill_value;
        }
        storage.stack.count = initial_capacity;
    }
    else
    {
        storage.heap.data = new short[initial_capacity];
        for (size_t i = 0; i < initial_capacity; i++)
        {
            storage.heap.data[i] = fill_value;
        }
        storage.heap.current_capacity = initial_capacity;
        storage.heap.count = initial_capacity;
    }
}

ShortArray::~ShortArray()
{
    if (is_on_heap())
        delete[] storage.heap.data;
}

ShortArray::ShortArray(const ShortArray &other)
{
    if (other.is_on_heap())
    {
        storage.heap.data = new short[other.storage.heap.current_capacity];
        for (size_t i = 0; i < other.storage.heap.count; i++)
        {
            storage.heap.data[i] = other.storage.heap.data[i];
        }
        storage.heap.current_capacity = other.storage.heap.current_capacity;
        storage.heap.count = other.storage.heap.count;
    }
    else
    {
        for (size_t i = 0; i < other.storage.stack.count; i++)
        {
            storage.stack.data[i] = other.storage.stack.data[i];
        }
        storage.stack.count = other.storage.stack.count;
    }
}

ShortArray::ShortArray(ShortArray &&moved)
{
    if (moved.is_on_heap())
    {
        storage.heap.data = moved.storage.heap.data;
        storage.heap.current_capacity = moved.storage.heap.current_capacity;
        storage.heap.count = moved.storage.heap.count;

        moved.storage.heap.data = nullptr;
        moved.storage.heap.current_capacity = 0;
        moved.storage.heap.count = 0;
    }
    else
    {
        for (size_t i = 0; i < moved.storage.stack.count; i++)
        {
            storage.stack.data[i] = moved.storage.stack.data[i];
        }
        storage.stack.count = moved.storage.stack.count;
        moved.storage.stack.count = 0;
    }
}

ShortArray &ShortArray::operator=(const ShortArray &other)
{
    if (this != &other)
    {
        if (is_on_heap())
            delete[] storage.heap.data;

        if (other.is_on_heap())
        {
            storage.heap.data = new short[other.storage.heap.current_capacity];
            for (size_t i = 0; i < other.storage.heap.count; i++)
            {
                storage.heap.data[i] = other.storage.heap.data[i];
            }
            storage.heap.current_capacity = other.storage.heap.current_capacity;
            storage.heap.count = other.storage.heap.count;
        }
        else
        {
            for (size_t i = 0; i < other.storage.stack.count; i++)
            {
                storage.stack.data[i] = other.storage.stack.data[i];
            }
            storage.stack.count = other.storage.stack.count;
        }
    }
    return *this;
}

ShortArray &ShortArray::operator=(ShortArray &&moved)
{
    if (this != &moved)
    {
        if (is_on_heap())
            delete[] storage.heap.data;

        if (moved.is_on_heap())
        {
            storage.heap.data = moved.storage.heap.data;
            storage.heap.current_capacity = moved.storage.heap.current_capacity;
            storage.heap.count = moved.storage.heap.count;

            moved.storage.heap.data = nullptr;
            moved.storage.heap.current_capacity = 0;
            moved.storage.heap.count = 0;
        }
        else
        {
            for (size_t i = 0; i < moved.storage.stack.count; i++)
            {
                storage.stack.data[i] = moved.storage.stack.data[i];
            }
            storage.stack.count = moved.storage.stack.count;
            moved.storage.stack.count = 0;
        }
    }
    return *this;
}

short &ShortArray::operator[](size_t index)
{
    if (is_on_heap())
    {
        if (index >= storage.heap.count)
        {
            throw std::out_of_range("Index was out of range");
        }
        return storage.heap.data[index];
    }
    else
    {
        if (index >= storage.stack.count)
        {
            throw std::out_of_range("Index was out of range");
        }
        return storage.stack.data[index];
    }
}

void ShortArray::push(short new_val)
{
    if (is_on_heap())
    {
        ensure_capacity(storage.heap.count + 1);
        storage.heap.data[storage.heap.count++] = new_val;
    }
    else
    {
        if (storage.stack.count < INLINE_CAPACITY)
            storage.stack.data[storage.stack.count++] = new_val;
        else
        {
            ensure_capacity(INLINE_CAPACITY + 1);
            storage.heap.data[storage.heap.count++] = new_val;
        }
    }
}

short ShortArray::pop()
{
    if (is_on_heap())
    {
        if (storage.heap.count == 0)
        {
            throw std::out_of_range("Array is empty");
        }
        return storage.heap.data[--storage.heap.count];
    }
    else
    {
        if (storage.stack.count == 0)
        {
            throw std::out_of_range("Array is empty");
        }
        return storage.stack.data[--storage.stack.count];
    }
}

size_t ShortArray::size() const
{
    return is_on_heap() ? storage.heap.count : storage.stack.count;
}

void ShortArray::resize(size_t new_size, short fill_value)
{
    if (is_on_heap())
    {
        ensure_capacity(new_size);
        if (new_size > storage.heap.current_capacity)
        {
            for (size_t i = storage.heap.count; i < new_size; i++)
            {
                storage.heap.data[i] = fill_value;
            }
        }
        storage.heap.count = new_size;

        // * try to get back into stack
        if (new_size <= INLINE_CAPACITY)
        {
            if (new_size <= INLINE_CAPACITY)
            {
                short *old_data = storage.heap.data;
                for (size_t i = 0; i < new_size; i++)
                {
                    storage.stack.data[i] = old_data[i];
                }
                storage.stack.count = new_size;

                delete[] old_data;
                storage.heap.data = nullptr;
                storage.heap.current_capacity = 0;
                storage.heap.count = 0;
            }
        }
    }
    else
    {
        // * try to get into heap
        if (new_size > INLINE_CAPACITY)
        {
            ensure_capacity(new_size);
            for (size_t i = storage.stack.count; i < new_size; i++)
            {
                storage.heap.data[i] = fill_value;
            }
            storage.heap.count = new_size;
            storage.stack.count = 0;
        }
        else
        {
            if (storage.stack.count < new_size)
            {
                for (size_t i = storage.stack.count; i < new_size; i++)
                {
                    storage.stack.data[i] = fill_value;
                }
            }
            storage.stack.count = new_size;
        }
    }
}
