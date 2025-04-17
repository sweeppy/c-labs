#include "Circle.hpp"

bool Circle::operator==(const Circle &other)
{
    return pointer == other.pointer && radius == other.radius;
}

const Pointer &Circle::get_pointer() const
{
    return pointer;
}

float Circle::get_square() const
{
    return M_PI * radius * radius;
}

float Circle::get_radius() const
{
    return radius;
}

void Circle::setPointer(float x, float y)
{
    pointer = Pointer(x, y);
}

void Circle::setRadius(float rad)
{
    radius = rad;
}

std::ostream &operator<<(std::ostream &os, const Circle circle)
{
    os << "Center: " << circle.get_pointer() << ";\n"
       << "Radius: " << circle.get_radius() << ";\n"
       << "Square: " << circle.get_square() << ".";
    return os;
}

std::istream &operator>>(std::istream &is, Circle &circle)
{
    float x, y;
    float radius;

    is >> x >> y >> radius;
    circle.setPointer(x, y);
    circle.setRadius(radius);

    return is;
}
