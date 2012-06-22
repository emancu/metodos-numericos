#include <matrix.h>
#include <types.h>
#include <tools.h>

void free_matrix_memory(Matrix* matrix){
  for(int i = 0; i < matrix->rows; i++)
    delete [] matrix->matrix[i];
  delete [] matrix->matrix;
}

void print_matrix(Matrix *matrix){
  printf("n = %d , m = %d\n" , matrix->rows, matrix->columns);

  for(int i = 0; i < matrix->rows; i++){
    for(int j = 0; j < matrix->rows; j++){
      printf("%lf \t" , matrix->matrix[i][j] );
    }
    printf("\n");
  }
  printf("\n");
  printf("\n");
}

Matrix multiplyMatrix(Matrix* a,Matrix* b ){
  Matrix result;
  result.rows = a->rows;
  result.columns = b->columns;

  result.matrix = new double*[result.rows];

  for(int i = 0; i < result.rows; i++){
    result.matrix[i] = new double[result.columns];
    for(int j = 0; j < result.columns; j++)
      result.matrix[i][j] = multiply_row_column(a,b,i,j);
  }

  return result;
}

void transpose(Matrix* m) {
  double aux;
  for(int i = 0; i < m->columns; i++){
    for(int j = i+1; j < m->rows; j++){
      aux = m->matrix[i][j];
      m->matrix[i][j] = m->matrix[j][i];
      m->matrix[j][i] = aux;
    }
  }
}

double multiply_row_column(Matrix* a, Matrix* b,int row,int column){
  double result = 0;
  for(int i = 0; i < a->columns; i++){
    result += (a->matrix[row][i] * b->matrix[i][column]);
  }
  return result;
}

void clone_matrix(const Matrix a, Matrix *clone) {
  clone->rows = a.rows;
  clone->columns = a.columns;

  clone->matrix = new double*[clone->rows];

  for(int i = 0; i < clone->rows; i++){
    clone->matrix[i] = new double[clone->columns];
    for(int j = 0; j < clone->columns; j++)
      clone->matrix[i][j] = a.matrix[i][j];
  }
}
