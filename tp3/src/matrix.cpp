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

void print_threeband_matrix(Matrix *matrix){
  printf("n = %d \n" , matrix->rows);

  for(int i = 0; i < matrix->rows; i++){
    for(int j = 0; j < matrix->rows; j++){
        if(i == j){
            printf("%lf \t" , matrix->matrix[1][i] );
        }else if ( j == i+1){
            printf("%lf \t" , matrix->matrix[0][i] );
        }else if (j == i-1){
            printf("%lf \t" , matrix->matrix[2][i + 1] );
        }else{
            printf("%lf \t" , 0.0);
        }
    }
    printf("\n");
  }
  printf("\n");
  printf("\n");
}

void print_normal_matrix(Matrix *matrix){
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

Matrix  multiplyMatrix(Matrix* a,Matrix* b ){
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


double multiply_row_column(Matrix* a, Matrix* b,int row,int column){
  double result = 0;
  for(int i = 0; i < a->columns; i++){
    result += (a->matrix[row][i] * b->matrix[i][column]);
  }
  return result;
}








