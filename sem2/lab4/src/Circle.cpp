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
    char sep; // * means symbol ,
    float x, y, radius;

    // * Skip word Center (
    is.ignore(100, '(');

    is >> x;

    is >> sep >> y;

    // * Skip word Radius:
    is.ignore(100, ':');

    is >> radius;

    // * Skip other symbols
    is.ignore(100, '\n');

    circle.setPointer(x, y);
    circle.setRadius(radius);
    return is;
}
