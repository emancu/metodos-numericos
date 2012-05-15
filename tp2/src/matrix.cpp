#include <matrix.h>
#include <tools.h>

Matrix build_matrix(double lambda, PGMInfo* pgm_info){
  // Each row has a column with the following form:
  // [ -1, 0, ..., 0, -1, lambda + 4, -1, 0, ..., 0, -1, pixel color ]
  // Where the distance between -1's and lambda + 4 (the diagonal element) is the pgm width.
  // Hence, the width of a column in matrix is: 2 * pgm width + 2
  // If the row belongs to an element of the border of the image, it looks like
  // [ 0, ..., 0, 1, 0, ..., 0, pixel color ]

  // Allocate matrix.
  Matrix matrix = new double*[pgm_info->height * pgm_info->width];
  int matrix_width = 2 * pgm_info->width + 2;
  for(int i = 0; i < pgm_info->height * pgm_info->width; i++)
    matrix[i] = new double[matrix_width];

  // Fill matrix with zeroes.
  for(int i = 0; i < pgm_info->height * pgm_info->width; i++)
    for(int j = 0; j < matrix_width; j++)
      matrix[i][j] = 0.0;

  int row_number = 0;
  for(int i = 0; i < pgm_info->height; i++){
    for(int j = 0; j < pgm_info->width; j++){
      // Saves the pixel color in the last element of the column
      matrix[row_number][matrix_width - 1] = pgm_info->pixels[i][j] * lambda;

      if(i == 0 || i == pgm_info->height - 1 || j == 0 || j == pgm_info->width - 1){
        matrix[row_number][pgm_info->width] = 1.0;
      }else{
        matrix[row_number][0]                   = -1.0;
        matrix[row_number][pgm_info->width - 1] = -1.0;
        matrix[row_number][pgm_info->width]     = lambda + 4.0;
        matrix[row_number][pgm_info->width + 1] = -1.0;
        matrix[row_number][matrix_width - 2]    = -1.0;
      }
      row_number++;
    }
  }

  return matrix;
}

void gauss(Matrix matrix, PGMInfo* pgm_info){
  //ver el tema de hasta donde hacerlo...
  for(int column_number = 1; column_number < pgm_info->height * pgm_info->width; column_number++){
    for(int row_number = column_number + 1; row_number <= column_number + pgm_info->width && row_number < pgm_info->width * pgm_info->height; row_number++){
      int index = column_number - (row_number - pgm_info->width);
      if(matrix[row_number][index] != 0.0){
        substract_rows(matrix, pgm_info, row_number, column_number);
      }
    }
  }
}

// column_number is the same row that will be used to substract.
void substract_rows(Matrix matrix, PGMInfo* pgm_info, int row_number, int column_number){
  double* row_to_use    = matrix[column_number];
  double* row_to_modify = matrix[row_number];
  int matrix_width = 2 * pgm_info->width + 2;

  int index = column_number - (row_number - pgm_info->width);
  // Coefficient needed to multiply the row_to_use to make a zero; ie: F2 - alpha*F1.
  double coefficient = row_to_modify[index] / row_to_use[pgm_info->width];

  row_to_modify[index] = 0.0;
  index ++;
  for(int i = pgm_info->width + 1; i < matrix_width - 1; i++){
    if(row_to_use[i] != 0.0){
      if(row_to_modify[index] != 0.0)
        row_to_modify[index] -= coefficient * row_to_use[i];
      else
        row_to_modify[index] = coefficient * row_to_use[i];
    }

    index++;
  }

  // Pixel.
  row_to_modify[matrix_width - 1] -= coefficient * row_to_use[matrix_width - 1];
}

void solve_equations(Matrix matrix, PGMInfo* pgm_info, double* results){
  int matrix_width = 2 * pgm_info->width + 2;
  for(int row = (pgm_info->height * pgm_info->width) - 1; row >= 0; row--){
    // Starts with the pixel value.
    double sum = matrix[row][matrix_width - 1];
    int i = 1;
    for(int column = pgm_info->width + 1; column < matrix_width - 1; column++){
       // Substract each of the known, previously calculated variables.
      if(matrix[row][column] != 0.0)
        sum -= matrix[row][column] * results[row + i];
      i++;
    }
    // Clear the final coefficient.
    results[row] = sum / matrix[row][pgm_info->width];
  }
}
