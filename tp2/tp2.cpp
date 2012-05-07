#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <map>

using namespace std;
typedef map<int, double> Row;
typedef map<int, Row> Matrix;

Matrix build_matrix(double, char*, int*);
void print_matrix(Matrix*);
void gauss(Matrix*, int);
void substract_rows(Matrix*, int, int);

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

  int size;
  Matrix matrix = build_matrix(lambda, picture, &size);
  gauss(&matrix, size);
  print_matrix(&matrix);

  return 0;
}

Matrix build_matrix(double lambda, char* picture, int* size){
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
      }

      matrix[row_number] = row;
      row_number++;
    }
  }
  *size = row_number++;

  fclose(file);
  return matrix;
}

void print_matrix(Matrix* matrix){
  Matrix::iterator row;
  for(row = matrix->begin(); row != matrix->end(); row++){
    printf("row: %d\n", row->first);
    Row::iterator pair;
    for(pair = row->second.begin(); pair != row->second.end(); pair++){
      printf("  position: %d\n",   pair->first);
      printf("  value   : %.5f\n", pair->second);
    }
    printf("\n");
  }
}

void gauss(Matrix* matrix, int size){
  for(int column_number = 0; column_number < size; column_number++){
    for(int row_number = column_number + 1; row_number < size; row_number++){
      if((*matrix)[row_number].count(column_number) > 0)
        substract_rows(matrix, row_number, column_number);
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
