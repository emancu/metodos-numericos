#ifndef __MATRIX__
#define __MATRIX__

#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

class Matrix {

  public:
    Matrix();
    Matrix(const Matrix&);
    Matrix(int rows, int cols);
    ~Matrix();

    /*
     * Metodos que modifican self
     */
    void identity();
    void zero();
    void delete_matrix();
    void left_multiply_by(const Matrix&);
    void right_multiply_by(const Matrix&);
    void transpose();
    void set(int, int, double);

    /*
     * Metodos que NO modifican self
     */
    int    rows() const;
    int    cols() const;
    void   print() const;
    double get(int, int) const;
    double* diagonal() const;
    double* sub_diagonal() const;
    double sum_lower_triangular() const;

  private:
    int _rows;
    int _cols;
    double** _matrix;

};

#endif
