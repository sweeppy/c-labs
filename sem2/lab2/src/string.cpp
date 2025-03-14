#include "string.hpp"
#include "colors.hpp"

void MyString::free_memory()
{
    if (data)
    {
        std::cout << RED << "Deleting: " << this << RESET << std::endl;
        delete[] data;
        data = nullptr;
        capacity = 0;
    }
}
void MyString::allocate_and_copy(const char *source, int length)
{
    data = new char[length + 1];
    capacity = length + 1;
    strncpy(data, source, length);
    data[length] = '\0';
}

MyString::MyString()
{
    data = new char[1];
    data[0] = '\0';
    capacity = 1;
}

MyString::MyString(const char *str)
{
    allocate_and_copy(str, strlen(str));
}

MyString::MyString(const MyString &other)
{
    allocate_and_copy(other.data, other.get_length());
}
MyString &MyString::operator=(const MyString &other)
{
    if (this != &other)
    {
        allocate_and_copy(other.data, other.get_length());
    }
    return *this;
}

MyString::~MyString()
{
    if (data)
    {
        std::cout << YELLOW << "Destroying: " << this << RESET << std::endl;
        free_memory();
    }
}

char MyString::get(int i) const
{
    if (i < 0 || i >= capacity)
        throw std::out_of_range("Index out of range");

    return data[i];
}
void MyString::set(int i, char c)
{
    if (i < 0 || i >= capacity)
        throw std::out_of_range("Index out of range");

    data[i] = c;
}

void MyString::set_new_string(const char *str)
{
    allocate_and_copy(str, strlen(str));
}

void MyString::print()
{
    if (!data)
        throw std::invalid_argument("String is not defined");

    std::cout << data << std::endl;
}

void MyString::read_line()
{
    free_memory();

    int buffer_size = 64;
    char *buffer = new char[buffer_size];
    int len = 0;

    while (true)
    {
        int ch = std::cin.get();

        if (ch == '\n' || ch == EOF)
            break;

        if (len + 1 >= buffer_size)
        {
            buffer_size *= 2;
            char *new_buffer = new char[buffer_size];
            strncpy(new_buffer, buffer, len);
            delete[] buffer;
            buffer = new_buffer;
        }

        buffer[len++] = static_cast<char>(ch);
    }

    buffer[len] = '\0';
    allocate_and_copy(buffer, len);
    delete[] buffer;
}

const char *MyString::get_data() const
{
    return data;
}

int MyString::get_length() const
{
    if (!data)
        return 0;

    return strlen(data);
}
