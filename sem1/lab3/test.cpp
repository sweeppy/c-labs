#include <iostream>
#include <cstring> // for memset to avoid warning
#include <ctime>

using std::cout, std::cin;

int main()
{
    char c = 'a';

    char *p1 = &c;
    const char *p2 = p1;
}
