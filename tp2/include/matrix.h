#ifndef __MATRIX__
#define __MATRIX__
#include <types.h>

Matrix build_matrix(double, char*, LowerBands*);
void gauss(Matrix*, LowerBands*);
void substract_rows(Matrix*, int, int);
void solve_equations(Matrix*, double*);

#endif