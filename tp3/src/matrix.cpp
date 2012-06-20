#include <matrix.h>
#include <types.h>
#include <tools.h>

void free_matrix_memory(Matrix* matrix){
  for(int i = 0; i < matrix->rows; i++)
    delete [] matrix->matrix[i];
  delete [] matrix->matrix;
}


void print_matrix(Matrix *matrix){
  printf("n = %d \n" , matrix->rows);

  for(int i = 0; i < 3; i++){ //el 3 es por como guardamos la matriz
    printf("\n");
    for(int j = 0; j < matrix->rows; j++)
      printf("%lf ," , matrix->matrix[i][j]);
  }
  printf("\n");
  printf("\n");
}
