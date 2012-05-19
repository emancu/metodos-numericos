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
  //indices para recorrer la matriz submuestreada independientemente de la original
  int k = 0,l = 0;
  double color;
  pgm_info.pixels = new double*[newHeight];
  for(i = 0; i < pgm_info.height; i += factor){
    pgm_info.pixels[k] = new double[newHeight];
    for(j = 0; j < pgm_info.width; j += factor){
      fread(pixel, 1, 1, file);
      //salteo los pixels que no utilizo
      fseek(file,factor - 1, SEEK_CUR);
      color = (double) (unsigned char) pixel[0];
      pgm_info.pixels[k][l] = color;
      l++;
    }
    //salteo las lineas de pixels que no utilizo
    fseek(file,pgm_info.height * (factor -1), SEEK_CUR);
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
  for(int i = 0; i < pgm_info->height * pgm_info->height; i++){
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
    printf("height =  %d \n", newHeight);
    for(int i = 0; i < newHeight; i++){
      for(int j = 0; j < newHeight; j++){
        printf("  %.0f", pgm_info->pixels[i][j]);
      }
      printf("\n \n");
    }
}

void print_results(double* results, PGMInfo* pgm_info, bool verification){
  int newHeight = ceil(pgm_info->height / pgm_info->factor);
  int size = newHeight * newHeight;
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

  char info[256];
  fputs("P5\n", outputFd);

  fputs("# Created by Mandrula INC\n", outputFd);

  sprintf(info, "%i %i\n" , pgm_info->width, pgm_info->height);
  fputs(info, outputFd);

  sprintf(info, "%i\n" , 255); //TODO cableado a 255
  fputs(info, outputFd);

  //TODO habria que ver si el results[i] > 255 => poner 255???? (sino pondria cualquier cosa)
  for(int i = 0; i < pgm_info->width * pgm_info->height; i++){
    fprintf(outputFd, "%c" ,(unsigned char)results[i]);
  }
}
