#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>


using namespace std;

void asciImage();

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

  FILE* file = fopen ("/home/alemata/facultad/metNum/tps/tp2/imagenes/64x64/blond.pgm", "r+b");
  FILE* output = fopen ("/home/alemata/facultad/metNum/tps/tp2/testA.pgm", "w");

  char name[256];
  char numero[256];


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

  sprintf(numero, "%i %i\n" , widthInt, heightInt);
  fputs(numero, output);

  sprintf(numero, "%i" , max);
  fputs(numero, output);

  for(i = 0; i <=256 ; i++){
    name[i] = 0x0;
    numero[i] = 0x0;
  }

  for(i = 0; i < heightInt ; i++){
     for(j=0; j < widthInt;j++){
        /*if( i == j ){
          name[0] = 0;
          fwrite(name,1,1,output);
          fread(name,1, 1, file);
        } else {*/
          fread(name,1, 1, file);
          printf ("%d  ", (unsigned char) name[0]);
          fwrite(name,1,1,output);

     }
    printf("\n\n");
  }

}


void asciImage(){
printf("holaaaa \n");

  FILE* file = fopen ("/home/alemata/facultad/metNum/tps/tp2/imagenes/64x64/prueba.pgm", "r");
  FILE* output = fopen ("/home/alemata/facultad/metNum/tps/tp2/test.pgm", "w");


  char name[256];
  char numero[256];

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


  sprintf(numero, "%i %i\n" , widthInt, heightInt);
  fputs(numero, output);

  sprintf(numero, "%i\n" , max);
  fputs(numero, output);


  printf("data = \n");
  int ch;

   for(i = 0; i < 7 ; i++){
     for(j=0; j < 24;j++){
        fscanf (file, "%d", &ch);
        if(j!=23){
          printf ("%d  ", ch);
          sprintf(numero, "%i  " ,ch);
          fputs(numero, output);
        }else{
          printf ("%d", ch);
          sprintf(numero, "%i\n" ,ch);
          fputs(numero, output);
        }
     }

    printf("\n");

  }

}
