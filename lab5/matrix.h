#include<iostream>
struct Matrix
{
    double **matrix;

    int width;
    int height;
};
void m_zero(Matrix *A, int m, int n);
void m_id(Matrix *A, int n);
void m_free(Matrix *A);
void m_copy(const Matrix *src, Matrix *dst);
int m_width(const Matrix *A);
int m_height(const Matrix *A);
double m_get(const Matrix *A, int i, int j);
void m_set(Matrix *A, int i, int j, double value);