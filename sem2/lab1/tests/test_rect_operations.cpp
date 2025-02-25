#include "../src/rect.hpp"
#include <cassert>

int main()
{

    Rect rect(10, 40, 40, 10);

    // move test
    rect.move(10, -10); // now coordinates: (20, 30, 50, 0)
    assert(rect.get_left() == 20);
    assert(rect.get_top() == 30);
    assert(rect.get_right() == 50);
    assert(rect.get_bottom() == 0);

    // inflate tests
    rect.inflate(5); // now coordinates: (15, 35, 55, -5)
    assert(rect.get_left() == 15);
    assert(rect.get_top() == 35);
    assert(rect.get_right() == 55);
    assert(rect.get_bottom() == -5);

    rect.inflate(5, 10); // now coordinates: (10, 45, 60, -15)
    assert(rect.get_left() == 10);
    assert(rect.get_top() == 45);
    assert(rect.get_right() == 60);
    assert(rect.get_bottom() == -15);

    rect.inflate(2, 3, 4, 5); // now coordinates: (8, 48, 64, -20)
    assert(rect.get_left() == 8);
    assert(rect.get_top() == 48);
    assert(rect.get_right() == 64);
    assert(rect.get_bottom() == -20);

    // Successfully completed tests
    std::cout << GREEN << "Operations tests passed!" << std::endl;
    return 0;
}
