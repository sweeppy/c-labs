#include <iostream>

class Pointer
{
private:
    float x;
    float y;

public:
    Pointer() : x(0), y(0) {}
    Pointer(float x, float y) : x(x), y(y) {}

    bool operator==(const Pointer &other);
    Pointer &operator=(const Pointer &other);

    float get_x() const;
    float get_y() const;
};

std::ostream &operator<<(std::ostream &os, const Pointer &pointer);
