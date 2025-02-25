#include "rect.hpp"

Rect::Rect()
{
    // this->left = 0;
    // this->top = 0;
    // this->right = 0;
    // this->bottom = 0;
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    std::cout << YELLOW << "Default constructor called. Address:" << this << RESET << std::endl;
}

Rect::Rect(int left, int top, int right, int bottom)
{
    this->x = left;
    this->y = bottom;
    this->width = right - left;
    this->height = top - bottom;
    std::cout << YELLOW << "Constructor with parameters called. Address:" << this << RESET << std::endl;
}

Rect::Rect(const Rect &other)
{
    // this->left = other.left;
    // this->top = other.top;
    // this->right = other.right;
    // this->bottom = other.bottom;
    this->x = other.x;
    this->y = other.y;
    this->width = other.width;
    this->height = other.height;
    std::cout << YELLOW << "Copy constructor called. Address:" << this << RESET << std::endl;
}

Rect::~Rect()
{
    std::cout << BLUE << "Destructor called. Address:" << this << RESET << std::endl;
}

// int Rect::get_right() { return right; }
int Rect::get_right() { return x + width; }
// int Rect::get_left() { return left; }
int Rect::get_left() { return x; }
// int Rect::get_top() { return top; }
int Rect::get_top() { return y + height; }
// int Rect::get_bottom() { return bottom; }
int Rect::get_bottom() { return y; }

// int Rect::get_width() { return std::abs(right - left); }
int Rect::get_width() { return width; }
// int Rect::get_height() { return std::abs(top - bottom); }
int Rect::get_height() { return height; }
// int Rect::get_square() { return get_width() * get_height(); }
int Rect::get_square() { return width * height; }

void Rect::set_all(int left, int top, int right, int bottom)
{
    this->x = left;
    this->y = bottom;
    this->width = right - left;
    this->height = top - bottom;
}

void Rect::set_width(int width)
{
    // right = left + std::abs(width);
    this->width = width;
}
void Rect::set_height(int height)
{
    // top = bottom + std::abs(height);
    this->height = height;
}

void Rect::inflate(int amount)
{
    // left -= amount;
    // right += amount;
    // top += amount;
    // bottom -= amount;
    x -= amount;
    y -= amount;
    width += amount * 2;
    height += amount * 2;
}
void Rect::inflate(int dw, int dh)
{
    // left -= dw;
    // top += dh;
    // right += dw;
    // bottom -= dh;
    x -= dw;
    y -= dh;
    width += dw * 2;
    height += dh * 2;
}
void Rect::inflate(int d_left, int d_top, int d_right, int d_bottom)
{
    // top += d_top;
    // bottom -= d_bottom;
    // left -= d_left;
    // right += d_right;
    x -= d_left;
    y -= d_bottom;
    width += d_right + d_left;
    height += d_top + d_bottom;
}

void Rect::move(int dx, int dy)
{
    // left += dx;
    // right += dx;
    // top += dy;
    // bottom += dy;
    x += dx;
    y += dy;
}

Rect bounding_rect(Rect r1, Rect r2)
{
    int left = std::min(r1.get_left(), r2.get_left());
    int right = std::max(r1.get_right(), r2.get_right());
    int top = std::max(r1.get_top(), r2.get_top());
    int bottom = std::min(r1.get_bottom(), r2.get_bottom());

    return Rect(left, top, right, bottom);
}

void print_rect(Rect &r)
{
    int width = r.get_width();
    int height = r.get_height();
    std::cout << "Rectangle " << width << "x" << height << ":" << std::endl;

    for (int i = 0; i < height; i++)
    {

        if (i == 0 || i == height - 1)
        {
            std::cout << " ";
            for (int j = 0; j < width; j++)
            {
                std::cout << "_";
            }
            std::cout << std::endl;
        }
        else
        {
            std::cout << "|";
            for (int j = 0; j < width; j++)
            {
                std::cout << " ";
            }
            std::cout << "|" << std::endl;
        }
    }
}
