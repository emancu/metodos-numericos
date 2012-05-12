#include <matrix.h>
#include <tools.h>

Matrix build_matrix(double lambda, char* picture, LowerBands* lower_bands){
  FILE* file = fopen(picture, "r+b");
  unsigned char pixel[256];
  int i,j;

  for(i = 0; i <= 1 ; i++){
    fgets((char*) pixel, 256, file);
  }

  int width, height, max;
  fscanf(file, "%d", &width);
  fscanf(file, "%d", &height);
  fscanf(file, "%d", &max);

  // Skips a newline.
  fread(pixel,1, 1, file);

  for(i = 0; i <= 256; i++){
    pixel[i] = 0x0;
  }

  Matrix matrix;
  LowerBands _lower_bands;
  for(i = 0; i < height * width; i++){
    set<int> rows;
    _lower_bands[i] = rows;
  }

  double color;
  int row_number = 0;

  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      Row row;
      fread(pixel, 1, 1, file);
      color = (double) (unsigned int) pixel[0];
      row[-1] = color;

      if(i == 0 || i == height - 1 || j == 0 || j == width - 1){
        row[row_number] = 1;
      }else{
        // Forms the row.
        row[row_number - width] = -1.0;
        row[row_number - 1]     = -1.0;
        row[row_number]         = lambda + 4.0;
        row[row_number + 1]     = -1.0;
        row[row_number + width] = -1.0;

        // Saves the row number for the column a *width* away from the diagonal.
        insert_row_number(&_lower_bands, row_number, row_number - width);

        // Saves the row number for the column previous the diagonal.
        insert_row_number(&_lower_bands, row_number, row_number - 1);
      }

      matrix[row_number] = row;
      row_number++;
    }
  }
  *lower_bands = _lower_bands;

  fclose(file);
  return matrix;
}

void gauss(Matrix* matrix, LowerBands* lower_bands){
  LowerBands::iterator lower_band; // first: column number, second: set of row numbers
  for(lower_band = lower_bands->begin(); lower_band != lower_bands->end(); lower_band++){
    //printf("  column %d\n", lower_band->first);
    set<int>::iterator row_number; // pointer to row number.
    for(row_number = lower_band->second.begin(); row_number != lower_band->second.end(); row_number++){
      //printf("    substracting row %d\n", *row_number);
      substract_rows(matrix, lower_bands, *row_number, lower_band->first);
    }

    // Fix iterator in case substract_rows adds values to lower_band.
    LowerBands::iterator new_iterator = lower_bands->begin();
    advance(new_iterator, distance(new_iterator, lower_band));
    lower_band = new_iterator;
  }
}

void substract_rows(Matrix* matrix, LowerBands* lower_bands, int row_number, int column_number){
  Row* row_to_modify = &((*matrix)[row_number]);
  Row* row_to_use    = &((*matrix)[column_number]);

  // Coefficient needed to multiply the row_to_use to make a zero; ie: F2 - alpha*F1.
  double coefficient = -1 * ((*row_to_modify)[column_number] / (*row_to_use)[column_number]);

  // First modify values present in the row to modify.
  Row::iterator pair; // first: column number, second is not used.
  for(pair = row_to_modify->begin(); pair != row_to_modify->end(); pair++){
    if(row_to_use->count(pair->first) > 0){
      (*row_to_modify)[pair->first] += coefficient * (*row_to_use)[pair->first];
    }
  }

  // For those columns where value is zero, the operation against row_to_use makes a new value.
  for(pair = row_to_use->upper_bound(column_number); pair != row_to_use->end(); pair++){
    if(row_to_modify->count(pair->first) == 0){
      (*row_to_modify)[pair->first] = coefficient * (*row_to_use)[pair->first];
      // If that new value is below the main diagonal, it will need to be triangulated later.
      if(row_number > pair->first){
        //printf("      for column %d inserting row %d\n", pair->first, row_number);
        insert_row_number(lower_bands, row_number, pair->first);
      }
    }
  }
}

void solve_equations(Matrix* matrix, double* results){
  Matrix::reverse_iterator row; // first: row number, second: Row
  for(row = matrix->rbegin(); row != matrix->rend(); row++){
    double sum = row->second[-1]; // Accumulates the numbers from the data and the other values.
    Row::iterator pair; // first: column number, second: value
    for(pair = row->second.upper_bound(row->first); pair != row->second.end(); pair++){
      sum -= pair->second * results[pair->first];
    }
    results[row->first] = sum / (*matrix)[row->first][row->first];
  }
}
