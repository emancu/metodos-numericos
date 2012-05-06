#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <map>

using namespace std;

void build_matrix(double);
void print_matrix(map<int, map<int, int> >);

int main(int argc, char* argv[]){
  static const char *optString = "l:";
  int c;
  int lambda; // it should be a double.
  // double lambda;

  while((c = getopt(argc, argv, optString)) != -1){
    switch(c){
      case 'l': { lambda = atof(optarg); break; }
      default:  { printf("Cannot parse.\n"); }
    }
  }

  if(lambda == NULL) lambda = 1;
  build_matrix(lambda);

  return 0;
}

void build_matrix(double lambda){
  FILE* file = fopen("imagenes/64x64/blond.pgm", "r+b");

  // buffers
  char name[256];
  char number[256];
  int i,j ;

  for(i = 0; i <= 1 ; i++){
    fgets(name, 256, file);
  }

  int width, height, max;
  fscanf (file, "%d", &width);
  fscanf (file, "%d", &height);
  fscanf (file, "%d", &max);

  sprintf(number, "%i %i\n", width, height);
  sprintf(number, "%i" , max);

  //leo el salto de linea
  fread(name,1, 1, file);

  for(i = 0; i <= 256; i++){
    name[i] = 0x0;
    number[i] = 0x0;
  }

  map<int, map<int, int> > matrix;
  int color;
  int pixel = 0;

  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      map<int, int> row;
      fread(name, 1, 1, file);
      color = (int) name[0];
      row[-1] = color;

      if(i == 0 || i == height - 1 || j == 0 || j == width - 1){
        row[pixel] = 1;
      }else{
        row[pixel - 4] = -1;
        row[pixel - 1] = -1;
        row[pixel]     = lambda + 4;
        row[pixel + 1] = -1;
        row[pixel + 4] = -1;
      }

      matrix[pixel] = row;
      pixel++;
    }
  }

  print_matrix(matrix);
}

void print_matrix(map<int, map<int, int> > matrix){
  map<int, map<int, int> >::iterator rows;
  for(rows = matrix.begin(); rows != matrix.end(); rows++){
    printf("row: %d\n", rows->first);
    map<int, int>::iterator pairs;
    for(pairs = rows->second.begin(); pairs != rows->second.end(); pairs++){
      printf("  position: %d\n", pairs->first);
      printf("  value   : %d\n", pairs->second);
    }
    printf("\n");
  }
}
