#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <map>

using namespace std;

void build_matrix(double, char*);
void print_matrix(map<int, map<int, double> >);

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

  if(lambda == NULL) lambda = 1;
  build_matrix(lambda, picture);

  return 0;
}

void build_matrix(double lambda, char* picture){
  FILE* file = fopen(picture, "r+b");

  // buffers
  unsigned char pixel[256];
  int i,j ;

  for(i = 0; i <= 1 ; i++){
    fgets((char*) pixel, 256, file);
  }

  int width, height, max;
  fscanf(file, "%d", &width);
  fscanf(file, "%d", &height);
  fscanf(file, "%d", &max);

  //leo el salto de linea
  fread(pixel,1, 1, file);

  for(i = 0; i <= 256; i++){
    pixel[i]  = 0x0;
  }

  map<int, map<int, double> > matrix;
  double color;
  int element = 0;

  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      map<int, double> row;
      fread(pixel, 1, 1, file);
      color = (double) (unsigned int) pixel[0];
      row[-1] = color;

      if(i == 0 || i == height - 1 || j == 0 || j == width - 1){
        row[element] = 1;
      }else{
        row[element - 4] = -1.0;
        row[element - 1] = -1.0;
        row[element]     = lambda + 4.0;
        row[element + 1] = -1.0;
        row[element + 4] = -1.0;
      }

      matrix[element] = row;
      element++;
    }
  }

  fclose(file);
  print_matrix(matrix);
}

void print_matrix(map<int, map<int, double> > matrix){
  map<int, map<int, double> >::iterator rows;
  for(rows = matrix.begin(); rows != matrix.end(); rows++){
    printf("row: %d\n", rows->first);
    map<int, double>::iterator pairs;
    for(pairs = rows->second.begin(); pairs != rows->second.end(); pairs++){
      printf("  position: %d\n", pairs->first);
      printf("  value   : %.5f\n", pairs->second);
    }
    printf("\n");
  }
}
