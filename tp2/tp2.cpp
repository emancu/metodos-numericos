#include <types.h>
#include <tools.h>

Matrix build_matrix(double, char*, LowerBands*);
void gauss(Matrix*, LowerBands*);
void substract_rows(Matrix*, int, int);
void solve_equations(Matrix*, double*);

int main(int argc, char* argv[]){
  static const char *optString = "l:f:";
  int c;
  char* picture;
  double lambda;

  while((c = getopt(argc, argv, optString)) != -1){
    switch(c){
      case 'l': { lambda  = atof(optarg); break; }
      case 'f': { picture = optarg; break; }
      default:  { printf("Cannot parse.\n"); }
    }
  }

  LowerBands lower_bands;
  Matrix matrix = build_matrix(lambda, picture, &lower_bands);

  gauss(&matrix, &lower_bands);

  double results[matrix.size()];
  solve_equations(&matrix, results);

  print_results(results, matrix.size());

  return 0;
}

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
        row[row_number - width] = -1.0;
        row[row_number - 1]     = -1.0;
        row[row_number]         = lambda + 4.0;
        row[row_number + 1]     = -1.0;
        row[row_number + width] = -1.0;

        // Saves the row numbers for each column of the lower bands.
        if(_lower_bands.count(row_number - width) == 0){
          list<int> rows(1, row_number);
          _lower_bands[row_number - width] = rows;
        }else if(_lower_bands[row_number - width].front() != row_number){
          _lower_bands[row_number - width].push_back(row_number);
        }

        if(_lower_bands.count(row_number - 1) == 0){
          list<int> rows(1, row_number);
          _lower_bands[row_number - 1] = rows;
        }else if(_lower_bands[row_number - width].front() != row_number){
          _lower_bands[row_number - 1].push_back(row_number);
        }
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
  LowerBands::iterator lower_band;
  for(lower_band = lower_bands->begin(); lower_band != lower_bands->end(); lower_band++){
    list<int>::iterator row;
    for(row = lower_band->second.begin(); row != lower_band->second.end(); row++){
      substract_rows(matrix, *row, lower_band->first);
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
  Matrix::reverse_iterator row;
  for(row = matrix->rbegin(); row != matrix->rend(); row++){
    double sum = row->second[-1];
    Row::iterator pair;
    for(pair = row->second.upper_bound(row->first); pair != row->second.end(); pair++){
      sum -= pair->second * results[pair->first];
    }
    results[row->first] = sum / (*matrix)[row->first][row->first];
  }
}
