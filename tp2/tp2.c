#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>


using namespace std;

void binaryImage();

/*
 *  Main
 */

int main(int argc, char* argv[]){
  binaryImage();

  return 0;
}

void binaryImage(){
  printf("holaaaa \n");

  FILE* file = fopen ("imagenes/128x128/amber.pgm", "r+b");
  FILE* output = fopen ("testA.pgm", "w");

  char name[256];
  char number[256];


  int i,j ;
  for(i = 0; i <= 1 ; i++){
    fgets(name, 256, file);
    printf("i = %d  = %s" , i, name);
    fputs(name, output);
  }

  int widthInt,heightInt,max;
  fscanf (file, "%d", &widthInt);
  fscanf (file, "%d", &heightInt);
  fscanf (file, "%d", &max);
  printf("width = %d \nheight = %d \nmax = %d \n" , widthInt, heightInt, max);

  sprintf(number, "%i %i\n" , widthInt, heightInt);
  fputs(number, output);

  sprintf(number, "%i" , max);
  fputs(number, output);

  //leo el salto de linea
  fread(name,1, 1, file);
  fwrite(name,1,1,output);

  for(i = 0; i <=256 ; i++){
    name[i] = 0x0;
    number[i] = 0x0;
  }

  for(i = 0; i < heightInt ; i++){
     for(j=0; j < widthInt;j++){
        if( i == j ){
          name[0] = 0;
          fwrite(name,1,1,output);
          fread(name,1, 1, file);
        } else {
          fread(name,1, 1, file);
          printf ("%d  ", (unsigned char) name[0]);
          fwrite(name,1,1,output);
        }
     }
    printf("\n\n");
  }

}
