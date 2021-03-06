#include <tools.h>
#include <time.h>
#include <math.h>


PGMInfo parse_pgm(char* picture, int factor){
  FILE* file = fopen(picture, "r+b");
  unsigned char pixel[256];
  int i, l, k = 0;
  PGMInfo pgm_info;
  double color;

  for(i = 0; i <= 1 ; i++)
    fgets((char*) pixel, 256, file);

  fscanf(file, "%d", &(pgm_info.width));
  fscanf(file, "%d", &(pgm_info.height));
  fscanf(file, "%d", &(pgm_info.max));

  pgm_info.factor = factor;
  pgm_info.fHeight = ceil(pgm_info.height * 1.0 / factor);
  pgm_info.fWidth  = ceil(pgm_info.width * 1.0 / factor);

  // Skips a newline.
  fread(pixel,1, 1, file);

  for(i = 0; i < 256; i++)
    pixel[i] = 0x0;

  pgm_info.pixels = new double*[pgm_info.fHeight];
  for(i = 0; i < pgm_info.fHeight; i++)
    pgm_info.pixels[i] = new double[pgm_info.fWidth];


  for(i = 0; i < pgm_info.height; i += factor){
    l = 0;
    for(int j = 0; j < pgm_info.width; j += factor){
      fread(pixel, 1, 1, file);
      color = (double) (unsigned char) pixel[0];
      pgm_info.pixels[k][l++] = color;

      //salteo los pixels que no utilizo
      if(j+factor >= pgm_info.width)
        fseek(file,pgm_info.width -j -1, SEEK_CUR);
      else
        fseek(file,factor - 1, SEEK_CUR);

    }
    //salteo las lineas de pixels que no utilizo (Eliminar filas)
    fseek(file,pgm_info.width * (factor -1), SEEK_CUR);
    k++;
  }

  fflush(file);
  fclose(file);
  return pgm_info;
}

void free_pixels_memory(PGMInfo* pgm_info){
  for(int i = 0; i < pgm_info->fHeight; i++)
    delete [] pgm_info->pixels[i];
  delete [] pgm_info->pixels;
}

void print_pgm_info(PGMInfo* pgm_info){
  printf("height =  %d \n", pgm_info->fHeight);
  for(int i = 0; i < pgm_info->fHeight; i++){
    for(int j = 0; j < pgm_info->fWidth; j++){
      printf("  %.0f", pgm_info->pixels[i][j]);
    }
    printf("\n \n");
  }
}

void print_results(double* results, PGMInfo* pgm_info, bool verification){
  int size = pgm_info->fHeight * pgm_info->fWidth;
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
  fprintf(outputFd, "P5\n");
  fprintf(outputFd, "# Created by Mandrula INC\n");
  fprintf(outputFd, "%i %i\n" , pgm_info->width, pgm_info->height);
  fprintf(outputFd, "%i\n" , pgm_info->max);

  //Usamos width y height original porque la imagen final tiene que tener las mismas proporciones.
  int factor = pgm_info->factor;
  double aux[pgm_info->width];

  for(int i = 0; i < pgm_info->fHeight; i++){
    for(int j = 0; j < pgm_info->fWidth; j++){
      for(int k=0; k < factor && (j*factor + k) < pgm_info->width; k++){ // Repetimos el pixel _factor_ veces
        aux[j*factor + k] = results[i * pgm_info->fWidth + j];
      }
    }

    // Fila completa, tenemos que escribirla *factor* veces en el archivo
    for(int j=0; j < min(factor, pgm_info->height - i*factor); j++)
      for(int k=0; k < pgm_info->width; k++)
        fprintf(outputFd, "%c", (unsigned char) aux[k]);
  }

  fflush(outputFd);
  fclose(outputFd);
}

/*
 * Restamos el minimo a todos y sacamos proporcionalmente el valor correspondiente.
 * Usando regla de tres simple. De esta manera el valor minimo, va a ser el cero.
 */
void saturate(double* results, int size, double min, double max){
  double constant = 255/(max-min);

  for(int i=0; i<size; i++)
    results[i] = (results[i]-min)*constant;
}
