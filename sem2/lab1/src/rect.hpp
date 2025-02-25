#include <iostream>
#include "colors.hpp"

class Rect
{
private:
    // int left;
    // int right;
    // int top;
    // int bottom;
    int x;
    int y;
    int width;
    int height;

public:
    Rect();
    Rect(int bottomLeft, int topLeft, int topRight, int bottomRight);
    Rect(const Rect &other);
    ~Rect();

    int get_right();
    int get_left();
    int get_top();
    int get_bottom();

    int get_width();
    int get_height();
    int get_square();

    void set_all(int left, int right, int top, int bottom);
    void set_width(int width);
    void set_height(int height);

    void inflate(int amount);
    void inflate(int dw, int dh);
    void inflate(int d_left, int d_right, int d_top, int d_bottom);

    void move(int dx = 0, int dy = 0);
};

Rect bounding_rect(Rect r1, Rect r2);

void print_rect(Rect &r);
