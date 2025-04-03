#include <iostream>
using namespace std;

struct A
{
    int a1 : 2;
    int a2 : 4;
    int a3 : 8;
    int a4 : 12;
};
struct B
{
    A *pa;
};
void f(const int &);

int main()
{
    const char y[] = "ABC";
}
