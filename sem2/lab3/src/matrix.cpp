#include "matrix.hpp"
#include "colors.hpp"

void Matrix::allocate_memory(int m, int n)
{
    std::cout << BLUE << "New memory for Matrix has been allocated" << RESET << std::endl;
    matrix = new double *[m];
    for (int i = 0; i < m; i++)
    {
        matrix[i] = new double[n];
    }

    width = n;
    height = m;
}

void Matrix::free_memory()
{
    if (matrix)
    {
        for (int i = 0; i < height; i++)
        {
            delete[] matrix[i];
            matrix[i] = nullptr;
        }
    }
    delete[] matrix;
    matrix = nullptr;
    width = 0;
    height = 0;
}

Matrix::Matrix(int n)
{
    allocate_memory(n, n);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            i == j ? matrix[i][j] = 1.0 : matrix[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(int m, int n, double fill_value)
{
    allocate_memory(m, n);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrix[i][j] = fill_value;
        }
    }
}

Matrix::Matrix(const Matrix &other)
{
    allocate_memory(other.height, other.width);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

Matrix::Matrix(Matrix &&moved)
{
    matrix = moved.matrix;
    width = moved.width;
    height = moved.height;

    moved.matrix = nullptr;
    moved.width = 0;
    moved.height = 0;
}

Matrix &Matrix::operator=(const Matrix &other)
{
    if (this != &other)
    {
        free_memory();
        allocate_memory(other.height, other.width);
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                matrix[i][j] = other.matrix[i][j];
            }
        }
    }
    return *this;
}

Matrix &Matrix::operator=(Matrix &&moved)
{
    if (this != &moved)
    {
        free_memory();
        matrix = moved.matrix;
        width = moved.width;
        height = moved.height;

        moved.matrix = nullptr;
        moved.width = 0;
        moved.height = 0;
    }
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &other)
{
    if (other.height != height || other.width != width)
    {
        throw std::invalid_argument("Matrixes do not match");
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrix[i][j] += other.matrix[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other)
{
    if (other.height != height || other.width != width)
    {
        throw std::invalid_argument("Matrixes do not match");
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrix[i][j] -= other.matrix[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator*=(const double value)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrix[i][j] *= value;
        }
    }
    return *this;
}

Matrix &Matrix::operator/=(const double value)
{
    if (value == 0)
        throw std::invalid_argument("Division by zero");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrix[i][j] /= value;
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &other)
{
    if (height != other.height || width != other.width)
        throw std::invalid_argument("Matrixes do not match");

    Matrix result(*this);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            result.matrix[i][j] += other.matrix[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix &other)
{
    if (height != other.height || width != other.width)
        throw std::invalid_argument("Matrixes do not match");

    Matrix result(*this);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            result.matrix[i][j] -= other.matrix[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &other)
{
    if (width != other.height)
        throw std::invalid_argument("Matrixes do not match");

    Matrix result(*this);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < width; k++)
            {
                sum += matrix[i][k] * other.matrix[k][j];
            }
            result.matrix[i][j] = sum;
        }
    }
    return result;
}
Matrix Matrix::operator*(const double value)
{
    Matrix result(*this);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            result.matrix[i][j] *= value;
        }
    }
    return result;
}
Matrix Matrix::operator/(const double value)
{
    if (value == 0)
        throw std::invalid_argument("Division by zero");

    Matrix result(*this);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            result.matrix[i][j] /= value;
        }
    }
    return result;
}

Matrix::~Matrix()
{
    free_memory();
}

double Matrix::get(int i, int j)
{
    if (i < 0 || j < 0 || i >= height || j >= width)
        throw std::out_of_range("Index out of range");

    return matrix[i][j];
}

void Matrix::set(int i, int j, double value)
{
    if (i < 0 || i >= height || j < 0 || j >= width)
        throw std::out_of_range("Index out of range");

    matrix[i][j] = value;
}

int Matrix::get_height()
{
    return height;
}
int Matrix::get_width()
{
    return width;
}

void Matrix::negate()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrix[i][j] = -matrix[i][j];
        }
    }
}

void Matrix::add_in_place(Matrix &other)
{
    if (other.width != width || other.height != height)
        throw std::invalid_argument("Matrix do not match");

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrix[i][j] += other.matrix[i][j];
        }
    }
}

Matrix Matrix::multiply(Matrix &other)
{
    if (width != other.height)
        throw std::invalid_argument("Matrix do not match");

    Matrix result(height, other.width);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < other.width; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < width; k++)
            {
                sum += matrix[i][k] * other.matrix[k][j];
            }
            result.matrix[i][j] = sum;
        }
    }

    return result;
}

void Matrix::copy_from(const Matrix &other)
{
    free_memory();

    allocate_memory(other.height, other.width);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

Matrix operator*(double value, const Matrix &matrix)
{
    Matrix result(matrix);
    result *= value;
    return result;
}
Matrix operator-(const Matrix &matrix)
{
    Matrix result(matrix);
    for (int i = 0; i < result.get_height(); i++)
    {
        for (int j = 0; j < result.get_width(); j++)
        {
            result.set(i, j, -result.get(i, j));
        }
    }
    return result;
}
