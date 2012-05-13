#ifndef __MATRIX__
#define __MATRIX__
#include <types.h>

Matrix build_matrix(double, PGMInfo*, LowerBands*);
void gauss(Matrix*, LowerBands*);
void substract_rows(Matrix*, LowerBands*, int, int);
void solve_equations(Matrix*, double*);

#endif
