#include <matrix.h>

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
        if(_lower_bands.count(row_number - width) == 0){
          set<int> rows;
          _lower_bands[row_number - width] = rows;
        }
        _lower_bands[row_number - width].insert(row_number);

        // Saves the row number for the column previous the diagonal.
        if(_lower_bands.count(row_number - 1) == 0){
          set<int> rows;
          _lower_bands[row_number - 1] = rows;
        }
        _lower_bands[row_number - 1].insert(row_number);
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
    set<int>::iterator row_number; // pointer to row number.
    for(row_number = lower_band->second.begin(); row_number != lower_band->second.end(); row_number++){
      substract_rows(matrix, *row_number, lower_band->first);
    }
  }
}

void substract_rows(Matrix* matrix, int row_number, int column_number){
  Row* row_to_modify = &((*matrix)[row_number]);
  Row* row_to_use    = &((*matrix)[column_number]);
  Row::iterator pair;
  for(pair = row_to_modify->begin(); pair != row_to_modify->end(); pair++){
    if(row_to_use->count(pair->first) > 0)
      (*row_to_modify)[pair->first] += (*row_to_use)[pair->first] / (*row_to_use)[column_number];
  }
}

void solve_equations(Matrix* matrix, double* results){
  Matrix::reverse_iterator row; // first: row number, second: Row
  for(row = matrix->rbegin(); row != matrix->rend(); row++){
    double sum = row->second[-1];
    Row::iterator pair; // first: column number, second: value
    for(pair = row->second.upper_bound(row->first); pair != row->second.end(); pair++){
      sum -= pair->second * results[pair->first];
    }
    results[row->first] = sum / (*matrix)[row->first][row->first];
  }
}
