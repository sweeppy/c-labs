#include "List.hpp"
#include "colors.hpp"

using std::cout;
using std::endl;

int main()
{
    cout << PURPLE << "=== START ===" << RESET << endl;
    ;
    List list;
    list.add_tail(Circle(Pointer(3, 3), 3));
    list.add_tail(Circle(Pointer(1, 1), 1));
    list.add_tail(Circle(Pointer(2, 2), 2));

    cout << "Before sort:\n"
         << list << endl;
    list.sort_by_square();
    cout << "After sort:\n"
         << list << endl;
    return 0;
}
