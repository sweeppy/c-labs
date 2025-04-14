#include "Pointer.hpp"
class Circle
{
private:
    Pointer pointer;
    float radius;

public:
    Circle() : pointer(Pointer()), radius(0) {}
    Circle(const Pointer ptr, float radius) : pointer(ptr), radius(radius) {}
    Circle(float x, float y, float radius) : pointer(Pointer(x, y)), radius(radius) {}
};
