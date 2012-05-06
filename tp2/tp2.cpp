#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <map>

using namespace std;

map<int, map<int, double> > build_matrix(double, char*);
void print_matrix(map<int, map<int, double> >);
void gauss(map<int, map<int, double> >, int);

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

  map<int, map<int, double> > matrix = build_matrix(lambda, picture);
  //print_matrix(matrix);
  gauss(matrix, 64 * 64);

  return 0;
}

map<int, map<int, double> > build_matrix(double lambda, char* picture){
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

  // skips a newline.
  fread(pixel,1, 1, file);

  for(i = 0; i <= 256; i++){
    pixel[i] = 0x0;
  }

  map<int, map<int, double> > matrix;
  double color;
  int row_number = 0;

  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      map<int, double> row;
      fread(pixel, 1, 1, file);
      color = (double) (unsigned int) pixel[0];
      row[-1] = color;

      if(i == 0 || i == height - 1 || j == 0 || j == width - 1){
        row[row_number] = 1;
      }else{
        row[row_number - 4] = -1.0;
        row[row_number - 1] = -1.0;
        row[row_number]     = lambda + 4.0;
        row[row_number + 1] = -1.0;
        row[row_number + 4] = -1.0;
      }

      matrix[row_number] = row;
      row_number++;
    }
  }

  fclose(file);
  return matrix;
}

void print_matrix(map<int, map<int, double> > matrix){
  map<int, map<int, double> >::iterator row;
  for(row = matrix.begin(); row != matrix.end(); row++){
    printf("row: %d\n", row->first);
    map<int, double>::iterator pair;
    for(pair = row->second.begin(); pair != row->second.end(); pair++){
      printf("  position: %d\n", pair->first);
      printf("  value   : %.5f\n", pair->second);
    }
    printf("\n");
  }
}

void gauss(map<int, map<int, double> > matrix, int size){
  for(int column_number = 0; column_number < size; column_number++){
    map<int, map<int, double> >::iterator row = matrix.begin();
    for(int i = 0; i < column_number; i++) row++; // jump unnecesary rows
    while(row != matrix.end()){
      if(row->first != column_number && row->second[column_number] != NULL){
        printf("Gotta pull my gauss!\n");
        printf("  row: %d column: %d\n", row->first, column_number);
        printf("  diagional: %f\n", matrix[column_number][column_number]);
        printf("  element to make zero is: %f\n", row->second[column_number]);
        //substract_rows(matrix, row->firsrt, column_number); implement this to make the substraction between the rows.
      }
      row++;
    }
  }
}
