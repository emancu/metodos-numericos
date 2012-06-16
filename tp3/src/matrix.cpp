#include <matrix.h>
#include <types.h>
#include <tools.h>

void free_matrix_memory(Matrix* matrix){
  for(int i = 0; i < matrix->rows; i++)
    delete [] matrix->matrix[i];
  delete [] matrix->matrix;
}
