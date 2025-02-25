#include "../src/rect.hpp"
#include <cassert>

int main()
{

    Rect rect(10, 20, 30, 10);

    // get_width, get_height, get_square tests
    assert(rect.get_width() == 20);
    assert(rect.get_height() == 10);
    assert(rect.get_square() == 200);

    // set_width test
    rect.set_width(30); // now coordinates: (10, 20, 40, 10)
    assert(rect.get_width() == 30);
    assert(rect.get_right() == 40);

    // set_height test
    rect.set_height(30); // now coordinates: (10, 40, 40, 10)
    assert(rect.get_height() == 30);
    assert(rect.get_top() == 40);

    // Successfully completed tests
    std::cout << GREEN << "Properties tests passed!" << std::endl;
    return 0;
}
