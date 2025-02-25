#include "../src/rect.hpp"
#include <cassert>

int main()
{
    // Default constructor
    Rect rect1;
    assert(rect1.get_left() == 0);
    assert(rect1.get_right() == 0);
    assert(rect1.get_bottom() == 0);
    assert(rect1.get_top() == 0);

    // Constructor with params
    Rect rect2(5, 10, 15, 5);
    assert(rect2.get_left() == 5);
    assert(rect2.get_top() == 10);
    assert(rect2.get_right() == 15);
    assert(rect2.get_bottom() == 5);

    // set_all test
    rect2.set_all(10, 20, 30, 10);
    assert(rect2.get_left() == 10);
    assert(rect2.get_top() == 20);
    assert(rect2.get_right() == 30);
    assert(rect2.get_bottom() == 10);

    // Successfully completed tests
    std::cout << GREEN << "Basic methods tests passed!" << std::endl;
    return 0;
}
