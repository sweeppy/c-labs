#include <iostream>
#include "string.hpp"
class TextWrapper
{
private:
    MyString input_text;
    int line_width;

    void print_line(const char *start, int length);

public:
    TextWrapper(const MyString &input, int width);

    void print_wrapped();
};
