#include "string.hpp"
#include "colors.hpp"

void MyString::free_memory()
{
    if (data)
    {
        // std::cout << RED << "Deleting: " << this << RESET << std::endl;
        delete[] data;
        data = nullptr;
        length = 0;
    }
}
void MyString::allocate_and_copy(const char *source, size_t len)
{
    std::cout << BLUE << "New memory for String has been allocated" << RESET << std::endl;
    data = new char[len + 1];
    strncpy(data, source, len);
    data[len] = '\0';
    length = len;
}

MyString::MyString()
{
    data = new char[1];
    data[0] = '\0';
    length = 0;
}

MyString::MyString(const char *str)
{
    allocate_and_copy(str, strlen(str));
}

MyString::MyString(const MyString &other)
{
    allocate_and_copy(other.data, other.length);
}

MyString::MyString(MyString &&moved)
{
    data = moved.data;
    length = moved.length;

    moved.data = nullptr;
    moved.length = 0;
}

MyString &MyString::operator=(MyString &&moved)
{
    if (this != &moved)
    {
        free_memory();
        data = moved.data;
        length = moved.length;
        moved.data = nullptr;
        moved.length = 0;
    }
    return *this;
}

MyString &MyString::operator=(const MyString &other)
{
    if (this != &other)
    {
        free_memory();
        allocate_and_copy(other.data, other.length);
    }

    return *this;
}

MyString &MyString::operator+=(const MyString &other)
{
    char *new_str = new char[length + other.length + 1];
    strcpy(new_str, data);
    strcat(new_str, other.data);
    delete[] data;
    data = new_str;
    length += other.length;

    return *this;
}
MyString &MyString::operator+=(const char *other)
{
    if (other)
    {
        size_t other_len = strlen(other);
        char *new_str = new char[length + other_len + 1];
        strcpy(new_str, data);
        strcat(new_str, other);
        delete[] data;
        data = new_str;
        length += other_len;
    }

    return *this;
}

bool MyString::operator==(const MyString &other) const
{
    return ((length == other.length) &&
            (strcmp(data, other.data) == 0));
}
bool MyString::operator!=(const MyString &other) const
{
    return !(*this == other);
}
bool MyString::operator<=(const MyString &other) const
{
    return ((strcmp(data, other.data) <= 0));
}
bool MyString::operator<(const MyString &other) const
{
    return ((strcmp(data, other.data) < 0));
}

bool MyString::operator==(const char *other) const
{
    return ((length == strlen(other)) &&
            (strcmp(data, other) == 0));
}
bool MyString::operator!=(const char *other) const
{
    return !(*this == other);
}
bool MyString::operator<=(const char *other) const
{
    return ((length <= strlen(other)) && (strcmp(data, other) <= 0));
}
bool MyString::operator<(const char *other) const
{
    return ((length < strlen(other)) && (strcmp(data, other) < 0));
}

char &MyString::operator[](size_t index)
{
    if (index >= length)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

MyString::~MyString()
{
    if (data)
    {
        // std::cout << YELLOW << "String destructor for object " << this << " called" << RESET << std::endl;
        free_memory();
    }
}

char MyString::get(size_t i) const
{
    if (i < 0 || i >= length)
        throw std::out_of_range("Index out of range");

    return data[i];
}
void MyString::set(size_t i, char c)
{
    if (i < 0 || i >= length)
        throw std::out_of_range("Index out of range");

    data[i] = c;
}

void MyString::set_new_string(const char *str)
{
    allocate_and_copy(str, strlen(str));
}

void MyString::print() const
{
    if (!data)
        throw std::invalid_argument("String is not defined");

    std::cout << data << std::endl;
}

void MyString::read_line()
{
    free_memory();

    size_t buffer_size = 64;
    char *buffer = new char[buffer_size];
    size_t len = 0;

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

size_t MyString::get_length() const
{
    return length;
}

MyString operator+(const MyString &left, const MyString &right)
{
    MyString result(left);
    result += right;
    return result;
}

MyString operator+(const MyString &left, const char *right)
{
    MyString result(left);
    result += right;
    return result;
}

MyString operator+(const char *left, const MyString &right)
{
    MyString result(left);
    result += right;
    return result;
}

bool operator==(const char *left, const MyString &right)
{
    return ((strcmp(left, right.get_data()) == 0));
}
bool operator!=(const char *left, const MyString &right)
{
    return !(left == right);
}
bool operator<=(const char *left, const MyString &right)
{
    return ((strcmp(left, right.get_data()) <= 0));
}
bool operator<(const char *left, const MyString &right)
{
    return ((strcmp(left, right.get_data()) < 0));
}

std::ostream &operator<<(std::ostream &os, const MyString &str)
{
    if (str.get_data())
    {
        os << str.get_data();
    }
    return os;
}

std::istream &operator>>(std::istream &is, MyString &str)
{
    str.read_line();
    return is;
}

MyString addTxtExtension(const MyString &path)
{
    return path + ".txt";
}
