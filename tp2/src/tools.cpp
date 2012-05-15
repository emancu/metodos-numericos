#include <tools.h>

PGMInfo parse_pgm(char* picture){
  FILE* file = fopen(picture, "r+b");
  unsigned char pixel[256];
  int i,j;
  PGMInfo pgm_info;

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

  double color;
  pgm_info.pixels = new double*[pgm_info.height];
  for(i = 0; i < pgm_info.height; i++){
    pgm_info.pixels[i] = new double[pgm_info.width];
    for(j = 0; j < pgm_info.width; j++){
      fread(pixel, 1, 1, file);
      color = (double) (unsigned int) pixel[0];
      pgm_info.pixels[i][j] = color;
    }
  }

  fclose(file);
  return pgm_info;
}

void free_pixels_memory(PGMInfo* pgm_info){
  for(int i = 0; i < pgm_info->height; i++)
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

void print_results(double* results, int size, bool verification){
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
  FILE* outputFd = fopen(output, "w");

  char* name;
  char info[256];
  name = "P5\n";
  fputs(name, outputFd);

  name = "# Created by Mandrula INC\n";
  fputs(name, outputFd);

  sprintf(info, "%i %i\n" , pgm_info->width, pgm_info->height);
  fputs(info, outputFd);

  sprintf(info, "%i\n" , 255); //TODO cableado a 255
  fputs(info, outputFd);

  for(int i = 0; i < pgm_info->width * pgm_info->height; i++){
    sprintf(info, "%c" ,(unsigned char) (unsigned int) results[i]);
    fputs(info, outputFd);
  }
}
