#include<iostream>
struct Matrix
{
    double **matrix = nullptr;

    int width = 0;
    int height = 0;
};

void m_zero(Matrix *A, int m, int n);
void m_id(Matrix *A, int n);
void m_copy(const Matrix *src, Matrix *dst);

double m_get(const Matrix *A, int i, int j);
void m_set(Matrix *A, int i, int j, double value);

void m_free(Matrix *A);

int m_width(const Matrix *A);
int m_height(const Matrix *A);

int m_add(Matrix *A, const Matrix *B);

void m_neg(Matrix *A);

int m_mult(const Matrix *A, const Matrix *B, Matrix *dst);

void m_hill_mult(const Matrix *A, const Matrix *B, Matrix *dst);