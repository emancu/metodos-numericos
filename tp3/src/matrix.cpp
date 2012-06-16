#include <matrix.h>
#include <tools.h>
#include <math.h>

Matrix build_matrix(double lambda, PGMInfo* pgm_info){
  // Each row has a column with the following form:
  // [ -1, 0, ..., 0, -1, lambda + 4, -1, 0, ..., 0, -1, pixel color ]
  // Where the distance between -1's and lambda + 4 (the diagonal element) is the pgm width.
  // Hence, the width of a column in matrix is: 2 * pgm width + 2
  // If the row belongs to an element of the border of the image, it looks like
  // [ 0, ..., 0, 1, 0, ..., 0, pixel color ]

  // Allocate matrix.
  int row_amount = pgm_info->fHeight * pgm_info->fWidth;
  int matrix_width = 2 * pgm_info->fWidth + 2;
  Matrix matrix = new double*[row_amount];

  // Fill matrix with zeroes.
  for(int i = 0; i < row_amount; i++){
    matrix[i] = new double[matrix_width];
    for(int j = 0; j < matrix_width; j++)
      matrix[i][j] = 0.0;
  }

  int row_number = 0;
  for(int i = 0; i < pgm_info->fHeight; i++){
    for(int j = 0; j < pgm_info->fWidth; j++){
      // Saves the pixel color in the last element of the column
      matrix[row_number][matrix_width - 1] = pgm_info->pixels[i][j] * lambda;

      if(i == 0 || i == pgm_info->fHeight - 1 || j == 0 || j == pgm_info->fWidth - 1){
        matrix[row_number][matrix_width - 1] = pgm_info->pixels[i][j];
        matrix[row_number][pgm_info->fWidth] = 1.0;
      }else{
        matrix[row_number][0]                     = -1.0;
        matrix[row_number][pgm_info->fWidth - 1]  = -1.0;
        matrix[row_number][pgm_info->fWidth]      = lambda + 4.0;
        matrix[row_number][pgm_info->fWidth + 1]  = -1.0;
        matrix[row_number][matrix_width - 2]      = -1.0;
      }
      row_number++;
    }
  }

  return matrix;
}

void gauss(Matrix matrix, PGMInfo* pgm_info){
  // cn = Column number | rn = Row number
  for(int cn = 1; cn < pgm_info->fHeight * pgm_info->fWidth; cn++){
    for(int rn = cn + 1; rn <= cn + pgm_info->fWidth && rn < pgm_info->fHeight * pgm_info->fWidth; rn++){
      int index = cn - (rn - pgm_info->fWidth);
      if(matrix[rn][index] != 0.0){
        substract_rows(matrix, pgm_info, rn, cn);
      }
    }
  }
}

// column_number is the same row that will be used to substract.
void substract_rows(Matrix matrix, PGMInfo* pgm_info, int row_number, int column_number){
  double* row_to_use    = matrix[column_number];
  double* row_to_modify = matrix[row_number];
  int matrix_width = 2 * pgm_info->fWidth + 2;


  int index = column_number - (row_number - pgm_info->fWidth);
  // Coefficient needed to multiply the row_to_use to make a zero; ie: F2 - alpha*F1.
  double coefficient = row_to_modify[index] / row_to_use[pgm_info->fWidth];

  row_to_modify[index] = 0.0;
  for(int i = pgm_info->fWidth + 1; i < matrix_width - 1; i++){
    index ++;
    if(row_to_use[i] != 0.0)
      row_to_modify[index] -= coefficient * row_to_use[i];
  }

  // Pixel.
  row_to_modify[matrix_width - 1] -= coefficient * row_to_use[matrix_width - 1];
}

void solve_equations(Matrix matrix, PGMInfo* pgm_info, double* results){
  int matrix_width = 2 * pgm_info->fWidth + 2;
  double minimum=256, maximum=0;

  for(int row = (pgm_info->fHeight * pgm_info->fWidth) - 1; row >= 0; row--){
    // Starts with the pixel value.
    double sum = matrix[row][matrix_width - 1];
    int i = 1;
    for(int column = pgm_info->fWidth + 1; column < matrix_width - 1; column++){
       // Substract each of the known, previously calculated variables.
      if(matrix[row][column] != 0.0)
        sum -= matrix[row][column] * results[row + i];
      i++;
    }

    results[row] = sum / matrix[row][pgm_info->fWidth];
    minimum = min(minimum, results[row]);
    maximum = max(maximum, results[row]);
  }

  saturate(results, pgm_info->fHeight * pgm_info->fWidth, minimum, maximum);
}
