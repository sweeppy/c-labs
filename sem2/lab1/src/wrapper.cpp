#include "wrapper.hpp"

TextWrapper::TextWrapper(const MyString &input, int width)
{
    input_text = input;
    line_width = width;
}

void TextWrapper::print_wrapped()
{
    const char *str = input_text.get_data();
    int len = input_text.get_length();

    int line_start = 0;
    int last_space = -1;
    int current_pos = 0;

    while (current_pos < len)
    {
        // Set space index
        if (str[current_pos] == ' ')
        {
            last_space = current_pos;
        }

        // Check string limit
        if (current_pos - line_start == line_width)
        {
            if (last_space != -1 && last_space > line_start)
            {
                // Break line by last space
                print_line(str + line_start, last_space - line_start);
                line_start = last_space + 1;
            }
            else
            {
                // Break line without spaces
                print_line(str + line_start, line_width);
                line_start += line_width;
            }
            last_space = -1; // Set default value for last_space
        }

        current_pos++;
    }

    // Print all symbols, that are left
    if (line_start < len)
    {
        print_line(str + line_start, len - line_start);
    }
}

void TextWrapper::print_line(const char *start, int length)
{
    for (int i = 0; i < length; ++i)
    {
        std::cout << start[i];
    }
    std::cout << std::endl;
}
