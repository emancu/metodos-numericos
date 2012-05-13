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
      matrix[row_number][matrix_width - 1] = pgm_info->pixels[i][j];

      if(i == 0 || i == pgm_info->height - 1 || j == 0 || j == pgm_info->width - 1){
        matrix[row_number][pgm_info->width] = 1;
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

// void gauss(Matrix* matrix, LowerBands* lower_bands){
//   LowerBands::iterator lower_band; // first: column number, second: set of row numbers
//   for(lower_band = lower_bands->begin(); lower_band != lower_bands->end(); lower_band++){
//     set<int>::iterator row_number; // pointer to row number.
//     for(row_number = lower_band->second.begin(); row_number != lower_band->second.end(); row_number++){
//       substract_rows(matrix, lower_bands, *row_number, lower_band->first);
//     }
// 
//     // Fix iterator in case substract_rows adds values to lower_band.
//     LowerBands::iterator new_iterator = lower_bands->begin();
//     advance(new_iterator, distance(new_iterator, lower_band));
//     lower_band = new_iterator;
//   }
// }
// 
// void substract_rows(Matrix* matrix, LowerBands* lower_bands, int row_number, int column_number){
//   Row* row_to_modify = &((*matrix)[row_number]);
//   Row* row_to_use    = &((*matrix)[column_number]);
// 
//   // Coefficient needed to multiply the row_to_use to make a zero; ie: F2 - alpha*F1.
//   double coefficient = -1 * ((*row_to_modify)[column_number] / (*row_to_use)[column_number]);
// 
//   // First modify values present in the row to modify.
//   Row::iterator pair; // first: column number, second is not used.
//   for(pair = row_to_modify->begin(); pair != row_to_modify->end(); pair++){
//     if(row_to_use->count(pair->first) > 0){
//       (*row_to_modify)[pair->first] += coefficient * (*row_to_use)[pair->first];
//     }
//   }
// 
//   // For those columns where value is zero, the operation against row_to_use makes a new value.
//   for(pair = row_to_use->upper_bound(column_number); pair != row_to_use->end(); pair++){
//     if(row_to_modify->count(pair->first) == 0){
//       (*row_to_modify)[pair->first] = coefficient * (*row_to_use)[pair->first];
//       // If that new value is below the main diagonal, it will need to be triangulated later.
//       if(row_number > pair->first){
//         insert_row_number(lower_bands, row_number, pair->first);
//       }
//     }
//   }
// }
// 
// void solve_equations(Matrix* matrix, double* results){
//   Matrix::reverse_iterator row; // first: row number, second: Row
//   for(row = matrix->rbegin(); row != matrix->rend(); row++){
//     double sum = row->second[-1]; // Accumulates the numbers from the data and the other values.
//     Row::iterator pair; // first: column number, second: value
//     for(pair = row->second.upper_bound(row->first); pair != row->second.end(); pair++){
//       sum -= pair->second * results[pair->first];
//     }
//     results[row->first] = sum / (*matrix)[row->first][row->first];
//   }
// }
