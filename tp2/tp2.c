#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <map>

using namespace std;

void buildMatrix(double);

/*
 *  Main
 */

int main(int argc, char* argv[]){
  static const char *optString = "l:";
  int c;
  double lambda;

  while((c = getopt(argc, argv, optString)) != -1){
    switch(c){
      case 'l': { lambda = atof(optarg); break; }
      default:  { printf("Cannot parse.\n"); }
    }
  }

  if(lambda == NULL) lambda = 1;
  buildMatrix(lambda);

  return 0;
}

void buildMatrix(double lambda){
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
  int element = 0;

  for(i = 0; i < height; i++){
    for(j = 0; j < width; j++){
      map<int, int> row;
      fread(name, 1, 1, file);
      color = (int) name[0];
      row[-1] = color;

      if(i == 0 || i == height - 1 || j == 0 || j == width - 1){
        row[element] = 1;
      }else{
        row[element - 4] = -1;
        row[element - 1] = -1;
        row[element]     = lambda + 4;
        row[element + 1] = -1;
        row[element + 4] = -1;
      }

      matrix[element] = row;
      element++;
    }
  }
}