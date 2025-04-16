#include "Circle.hpp"

bool Circle::operator==(const Circle &other)
{
    return pointer == other.pointer && radius == other.radius;
}

const Pointer &Circle::get_pointer() const
{
    return pointer;
}

double Circle::get_square() const
{
    return M_PI * radius * radius;
}

float Circle::get_radius() const
{
    return radius;
}

std::ostream &operator<<(std::ostream &os, const Circle circle)
{
    os << "Center: " << circle.get_pointer() << ";\n"
       << "Radius: " << circle.get_radius() << ";\n"
       << "Square: " << circle.get_square() << ".";
    return os;
}
