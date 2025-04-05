#include <iostream>

class MyString
{
private:
    char *data;
    size_t length;

    void allocate_and_copy(const char *source, size_t length);
    void free_memory();

public:
    MyString();
    MyString(const char *str);

    MyString(const MyString &other);
    MyString(MyString &&moved);

    MyString &operator=(const MyString &other);
    MyString &operator=(MyString &&moved);

    MyString &operator+=(const MyString &other);
    MyString &operator+=(const char *other);

    bool operator==(const MyString &other);
    bool operator!=(const MyString &other);
    bool operator<=(const MyString &other);
    bool operator<(const MyString &other);

    bool operator==(const char *other);
    bool operator!=(const char *other);
    bool operator<=(const char *other);
    bool operator<(const char *other);

    char &operator[](size_t index);

    ~MyString();

    char get(size_t i) const;
    void set(size_t i, char c);

    void set_new_string(const char *str);
    void print();
    void read_line();

    const char *get_data() const;
    size_t get_length() const;
};

MyString operator+(const MyString &left, const MyString &right);
MyString operator+(const MyString &left, const char *right);
MyString operator+(const char *left, const MyString &right);

bool operator==(const char *left, const MyString &right);
bool operator!=(const char *left, const MyString &right);
bool operator<=(const char *left, const MyString &right);
bool operator<(const char *left, const MyString &right);
