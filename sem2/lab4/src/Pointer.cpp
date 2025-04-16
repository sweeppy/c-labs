#include "Pointer.hpp"

bool Pointer::operator==(const Pointer &other)
{
    return x == other.x && y == other.y;
}

float Pointer::get_x() const
{
    return x;
}
float Pointer::get_y() const
{
    return y;
}

std::ostream &operator<<(std::ostream &os, const Pointer &pointer)
{
    os << "( " << pointer.get_x() << ", " << pointer.get_y() << " )";
    return os;
}
