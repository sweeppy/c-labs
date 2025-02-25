#include <iostream>

class MyString
{
private:
    char *data;
    int capacity;

    void allocate_and_copy(const char *source, int length);
    void free_memory();

public:
    MyString();
    MyString(const char *str);

    MyString(const MyString &other);
    MyString &operator=(const MyString &other);
    ~MyString();

    char get(int i);
    void set(int i, char c);

    void set_new_string(const char *str);
    void print();
    void read_line();

    const char *get_data();
    int get_length();
};
