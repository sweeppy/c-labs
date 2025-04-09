#include "shortArray.hpp"
#include "colors.hpp"
#include <iostream>
#include <algorithm>
#include <cstdint>

bool ShortArray::is_on_heap() const
{
    // std::cout << CYAN << "[is_on_heap] Checking if on heap: " << storage.heap.data.bits.is_heap << RESET << std::endl;
    return storage.heap.data.bits.is_heap == 1;
}

size_t ShortArray::get_size() const
{
    size_t size = is_on_heap() ? storage.heap.count : storage.stack.count;
    // std::cout << CYAN << "[get_size] Current size: " << size << RESET << std::endl;
    return size;
}

void ShortArray::set_size(size_t size)
{
    // std::cout << CYAN << "[set_size] Setting size to: " << size << RESET << std::endl;
    if (is_on_heap())
    {
        storage.heap.count = size;
    }
    else
    {
        storage.stack.count = size;
    }
}

void ShortArray::ensure_capacity(size_t required_capacity)
{
    // std::cout << CYAN << "[ensure_capacity] Ensuring capacity: " << required_capacity << RESET << std::endl;

    if (is_on_heap())
    {
        // std::cout << CYAN << "[ensure_capacity] Current heap capacity: " << storage.heap.current_capacity << RESET << std::endl;
        if (storage.heap.current_capacity >= required_capacity)
            return;

        size_t new_capacity = std::max(storage.heap.current_capacity * 2, required_capacity);
        // std::cout << CYAN << "[ensure_capacity] Allocating new heap capacity: " << new_capacity << RESET << std::endl;
        short *new_data = new short[new_capacity];

        for (size_t i = 0; i < storage.heap.count; i++)
        {
            new_data[i] = reinterpret_cast<short *>(storage.heap.data.bits.ptr)[i];
        }

        delete[] reinterpret_cast<short *>(storage.heap.data.bits.ptr);
        storage.heap.data.bits.ptr = reinterpret_cast<uintptr_t>(new_data);
        storage.heap.current_capacity = new_capacity;
    }
    else
    {
        if (required_capacity <= INLINE_CAPACITY)
        {
            // std::cout << CYAN << "[ensure_capacity] No need to switch to heap" << RESET << std::endl;
            return;
        }

        size_t new_capacity = std::max(INLINE_CAPACITY * 2, required_capacity);
        // std::cout << CYAN << "[ensure_capacity] Switching to heap with capacity: " << new_capacity << RESET << std::endl;
        short *new_data = new short[new_capacity];

        for (size_t i = 0; i < storage.stack.count; i++)
        {
            new_data[i] = storage.stack.data[i];
        }

        storage.heap.data.bits.ptr = reinterpret_cast<uintptr_t>(new_data);
        storage.heap.data.bits.is_heap = 1;
        storage.heap.current_capacity = new_capacity;
        storage.heap.count = storage.stack.count;
    }
}

ShortArray::ShortArray()
{
    // std::cout << CYAN << "[ShortArray] Default constructor" << RESET << std::endl;
    storage.stack.count = 0;
    storage.heap.data.bits.is_heap = 0;
}

ShortArray::ShortArray(size_t initial_capacity, short fill_value)
{
    // std::cout << CYAN << "[ShortArray] Constructor with initial_capacity: " << initial_capacity << ", fill_value: " << fill_value << RESET << std::endl;

    if (initial_capacity <= INLINE_CAPACITY)
    {
        for (size_t i = 0; i < initial_capacity; i++)
        {
            storage.stack.data[i] = fill_value;
        }
        storage.stack.count = initial_capacity;
        storage.heap.data.bits.is_heap = 0;
    }
    else
    {
        short *new_data = new short[initial_capacity];
        for (size_t i = 0; i < initial_capacity; i++)
        {
            new_data[i] = fill_value;
        }

        storage.heap.data.bits.ptr = reinterpret_cast<uintptr_t>(new_data);
        storage.heap.data.bits.is_heap = 1;
        storage.heap.current_capacity = initial_capacity;
        storage.heap.count = initial_capacity;
    }
}

ShortArray::~ShortArray()
{
    // std::cout << CYAN << "[~ShortArray] Destructor called" << RESET << std::endl;
    if (is_on_heap())
    {
        delete[] reinterpret_cast<short *>(storage.heap.data.bits.ptr);
        // std::cout << CYAN << "[~ShortArray] Heap memory deleted" << RESET << std::endl;
    }
}

ShortArray::ShortArray(const ShortArray &other)
{
    // std::cout << CYAN << "[ShortArray] Copy constructor" << RESET << std::endl;
    if (other.is_on_heap())
    {
        short *new_data = new short[other.storage.heap.current_capacity];
        for (size_t i = 0; i < other.storage.heap.count; i++)
        {
            new_data[i] = reinterpret_cast<short *>(other.storage.heap.data.bits.ptr)[i];
        }

        storage.heap.data.bits.ptr = reinterpret_cast<uintptr_t>(new_data);
        storage.heap.data.bits.is_heap = 1;
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
        storage.heap.data.bits.is_heap = 0;
    }
}

ShortArray::ShortArray(ShortArray &&moved)
{
    // std::cout << CYAN << "[ShortArray] Move constructor" << RESET << std::endl;
    if (moved.is_on_heap())
    {
        storage.heap.data = moved.storage.heap.data;
        storage.heap.current_capacity = moved.storage.heap.current_capacity;
        storage.heap.count = moved.storage.heap.count;

        moved.storage.heap.data.bits.ptr = 0;
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
    // std::cout << CYAN << "[operator=] Copy assignment operator" << RESET << std::endl;
    if (this != &other)
    {
        if (is_on_heap())
        {
            delete[] reinterpret_cast<short *>(storage.heap.data.bits.ptr);
        }

        if (other.is_on_heap())
        {
            short *new_data = new short[other.storage.heap.current_capacity];
            for (size_t i = 0; i < other.storage.heap.count; i++)
            {
                new_data[i] = reinterpret_cast<short *>(other.storage.heap.data.bits.ptr)[i];
            }

            storage.heap.data.bits.ptr = reinterpret_cast<uintptr_t>(new_data);
            storage.heap.data.bits.is_heap = 1;
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
            storage.heap.data.bits.is_heap = 0;
        }
    }
    return *this;
}

ShortArray &ShortArray::operator=(ShortArray &&moved)
{
    // std::cout << CYAN << "[operator=] Move assignment operator" << RESET << std::endl;
    if (this != &moved)
    {
        if (is_on_heap())
        {
            delete[] reinterpret_cast<short *>(storage.heap.data.bits.ptr);
        }

        if (moved.is_on_heap())
        {
            storage.heap.data = moved.storage.heap.data;
            storage.heap.current_capacity = moved.storage.heap.current_capacity;
            storage.heap.count = moved.storage.heap.count;

            moved.storage.heap.data.bits.ptr = 0;
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
    // std::cout << CYAN << "[operator[]] Accessing index: " << index << RESET << std::endl;
    if (index >= get_size())
    {
        throw std::out_of_range("Index out of range");
    }

    if (is_on_heap())
    {
        return reinterpret_cast<short *>(storage.heap.data.bits.ptr)[index];
    }
    else
    {
        return storage.stack.data[index];
    }
}

void ShortArray::push(short new_val)
{
    // std::cout << CYAN << "[push] Pushing value: " << new_val << RESET << std::endl;
    ensure_capacity(get_size() + 1);
    if (is_on_heap())
    {
        reinterpret_cast<short *>(storage.heap.data.bits.ptr)[storage.heap.count] = new_val;
        storage.heap.count++;
    }
    else
    {
        storage.stack.data[storage.stack.count] = new_val;
        storage.stack.count++;
    }
}

short ShortArray::pop()
{
    // std::cout << CYAN << "[pop] Popping value" << RESET << std::endl;
    if (get_size() == 0)
    {
        throw std::out_of_range("Array is empty");
    }

    short value;
    if (is_on_heap())
    {
        value = reinterpret_cast<short *>(storage.heap.data.bits.ptr)[storage.heap.count - 1];
        storage.heap.count--;
    }
    else
    {
        value = storage.stack.data[storage.stack.count - 1];
        storage.stack.count--;
    }
    return value;
}

size_t ShortArray::size() const
{
    // std::cout << CYAN << "[size] Getting size" << RESET << std::endl;
    return get_size();
}

void ShortArray::resize(size_t new_size, short fill_value)
{
    // std::cout << CYAN << "[resize] Resizing to: " << new_size << ", fill_value: " << fill_value << RESET << std::endl;

    if (new_size == get_size())
        return;

    size_t current_size = get_size();

    // heap to stack
    if (is_on_heap() && new_size <= INLINE_CAPACITY)
    {
        // std::cout << CYAN << "[resize] Switching from heap to stack; size: " << new_size << RESET << std::endl;
        short *heap_data = reinterpret_cast<short *>(storage.heap.data.bits.ptr);
        size_t copy_size = std::min(current_size, new_size);

        for (size_t i = 0; i < copy_size; i++)
        {
            storage.stack.data[i] = heap_data[i];
        }

        for (size_t i = copy_size; i < new_size; i++)
        {
            storage.stack.data[i] = fill_value;
        }

        delete[] heap_data;

        storage.stack.count = new_size;
        storage.heap.data.bits.is_heap = 0;
        storage.heap.current_capacity = 0;
        return;
    }

    ensure_capacity(new_size);

    if (new_size > current_size)
    {
        for (size_t i = current_size; i < new_size; i++)
        {
            if (is_on_heap())
            {
                reinterpret_cast<short *>(storage.heap.data.bits.ptr)[i] = fill_value;
            }
            else
            {
                storage.stack.data[i] = fill_value;
            }
        }
    }

    set_size(new_size);
}