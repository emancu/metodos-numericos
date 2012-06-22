#ifndef __MATRIX__
#define __MATRIX__

#include <types.h>

void free_matrix_memory(Matrix*);
void print_matrix(Matrix *matrix);
Matrix multiplyMatrix(Matrix* a,Matrix* b );
double multiply_row_column(Matrix* a, Matrix* b,int i,int j);

void clone_matrix(const Matrix, Matrix *);
void transpose(Matrix *);

#endif
