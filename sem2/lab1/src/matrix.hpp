#include <iostream>

class Matrix
{
private:
    double **matrix;
    int width;
    int height;

    void allocate_memory(int m, int n);
    void free_memory();

public:
    Matrix(int n);
    Matrix(int m, int n, double fill_value = 0);

    Matrix(const Matrix &other);

    ~Matrix();

    double get(int i, int j);
    void set(int i, int j, double value);

    int get_height();
    int get_width();

    void negate();

    void add_in_place(Matrix &other);

    Matrix multiply(Matrix &other);

    void copy_from(const Matrix &other);
};
