#include "matrix.hpp"

void Matrix::allocate_memory(int m, int n)
{
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
    for (int i = 0; i < height; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
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
