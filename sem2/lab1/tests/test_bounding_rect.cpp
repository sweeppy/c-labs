#include "../src/rect.hpp"
#include <cassert>

int main()
{
    // bounding_rect test
    Rect rect3(0, 10, 20, 0);
    Rect rect4(10, 30, 40, 10);
    Rect bounding = bounding_rect(rect3, rect4);
    assert(bounding.get_left() == 0);
    assert(bounding.get_top() == 30);
    assert(bounding.get_right() == 40);
    assert(bounding.get_bottom() == 0);

    // Successfully completed tests
    std::cout << GREEN << "Bounding rect tests passed!" << std::endl;
    return 0;
}
