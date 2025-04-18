#include "Pointer.hpp"
#include <iostream>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Circle
{
private:
    Pointer pointer;
    float radius;

public:
    Circle() : pointer(Pointer()), radius(0) {}
    Circle(const Pointer ptr, float radius) : pointer(ptr), radius(radius) {}
    Circle(float x, float y, float radius) : pointer(Pointer(x, y)), radius(radius) {}

    bool operator==(const Circle &other);

    const Pointer &get_pointer() const;

    float get_square() const;
    float get_radius() const;

    void setPointer(float x, float y);
    void setRadius(float radius);
};
std::ostream &operator<<(std::ostream &os, const Circle circle);
std::istream &operator>>(std::istream &is, Circle &circle);
