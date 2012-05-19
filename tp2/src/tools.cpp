#include <tools.h>
#include <time.h>
#include <math.h>


PGMInfo parse_pgm(char* picture, int factor){
  FILE* file = fopen(picture, "r+b");
  unsigned char pixel[256];
  int i,j;
  PGMInfo pgm_info;
  pgm_info.factor = factor;

  for(i = 0; i <= 1 ; i++){
    fgets((char*) pixel, 256, file);
  }

  fscanf(file, "%d", &(pgm_info.width));
  fscanf(file, "%d", &(pgm_info.height));
  fscanf(file, "%d", &(pgm_info.max));

  // Skips a newline.
  fread(pixel,1, 1, file);

  for(i = 0; i <= 256; i++){
    pixel[i] = 0x0;
  }


  int newHeight = ceil(pgm_info.height / factor);
  int newWidth  = ceil(pgm_info.width / factor);
  //indices para recorrer la matriz submuestreada independientemente de la original
  int k = 0,l = 0;
  double color;
  pgm_info.pixels = new double*[newHeight];

  for(i = 0; i < pgm_info.height; i += factor){
    pgm_info.pixels[k] = new double[newWidth];
    for(j = 0; j < pgm_info.width; j += factor){
      fread(pixel, 1, 1, file);
      //salteo los pixels que no utilizo
      fseek(file,factor - 1, SEEK_CUR);
      color = (double) (unsigned char) pixel[0];
      pgm_info.pixels[k][l] = color;
      l++;
    }
    //salteo las lineas de pixels que no utilizo (Eliminar filas)
    fseek(file,pgm_info.width * (factor -1), SEEK_CUR);
    k++;
    l = 0;
  }

  fclose(file);
  return pgm_info;
}

void free_pixels_memory(PGMInfo* pgm_info){
  int newHeight = ceil(pgm_info->height / pgm_info->factor);
  for(int i = 0; i < newHeight; i++)
    delete [] pgm_info->pixels[i];
  delete [] pgm_info->pixels;
}

void print_pretty_matrix(Matrix matrix, PGMInfo* pgm_info){
  printf("print_pretty_matrix Deprecated");
  return;
  for(int i = 0; i < pgm_info->height * pgm_info->width; i++){
    for(int k = 0; k < i; k++) printf(" ");
    for(int j = 0; j < 2 * pgm_info->width + 2; j++){
      if(matrix[i][j] >= 0.0){
        printf("  %.5f", matrix[i][j]);
      }else if(matrix[i][j] >= 0.0){
        printf(" %.5f", matrix[i][j]);
      }
    }
    printf("\n");
  }
}

void print_pgm_info(PGMInfo* pgm_info){
    int newHeight = ceil(pgm_info->height / pgm_info->factor);
    int newWidth  = ceil(pgm_info->width / pgm_info->factor);
    printf("height =  %d \n", newHeight);
    for(int i = 0; i < newHeight; i++){
      for(int j = 0; j < newWidth; j++){
        printf("  %.0f", pgm_info->pixels[i][j]);
      }
      printf("\n \n");
    }
}

void print_results(double* results, PGMInfo* pgm_info, bool verification){
  int newHeight = ceil(pgm_info->height / pgm_info->factor);
  int newWidth  = ceil(pgm_info->width / pgm_info->factor);
  int size = newHeight * newWidth;
  for(int i = 0; i < size; i++){
    if(verification){
      unsigned int color = (unsigned int) results[i];
      if(0 <= color && color < 256)
        printf(".");
      else
        printf("F variable %d is %d", i, color);
    }else{
      printf("%.5f ", results[i]);
    }

    if(i % size == size - 1) printf("\n");
  }
}

void create_new_picture(double* results, char* output, PGMInfo* pgm_info){
  //Usamos width y height original porque la imagen final tiene que tener las mismas proporciones.
  FILE* outputFd = fopen(output, "w");
  fprintf(outputFd, "P5\n");
  fprintf(outputFd, "# Created by Mandrula INC\n");
  fprintf(outputFd, "%i %i\n" , pgm_info->width, pgm_info->height);
  fprintf(outputFd, "%i\n" , pgm_info->max);

  //TODO habria que ver si el results[i] > 255 => poner 255???? (sino pondria cualquier cosa)
  for(int i = 0; i < pgm_info->width * pgm_info->height; i++){
    fprintf(outputFd, "%c" ,(unsigned char)results[i]);
  }
}
