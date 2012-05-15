#ifndef __MATRIX__
#define __MATRIX__
#include <types.h>

Matrix build_matrix(double, PGMInfo*);
void gauss(Matrix, PGMInfo*);
void substract_rows(Matrix, PGMInfo*, int, int);
void solve_equations(Matrix, PGMInfo*, double*);

#endif
