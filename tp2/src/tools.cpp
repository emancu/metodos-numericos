#include <tools.h>
#include <time.h>
#include <math.h>


PGMInfo parse_pgm(char* picture, int factor){
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
      color = (double) (unsigned int) pixel[0];
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

void print_pgm_info(PGMInfo* pgm_info, double factor){
    int newHeight = ceil(pgm_info->height / factor);
    printf("height =  %d \n", newHeight);
    for(int i = 0; i < newHeight; i++){
      for(int j = 0; j < newHeight; j++){
        printf("  %.0f", pgm_info->pixels[i][j]);
      }
      printf("\n \n");
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

void createWithSaltPeperNoise(double * results, double p, double q, char* output, PGMInfo* pgm_info){
   /* initialize random seed: */
  double random;
  srand ( time(NULL) );

  int h = 0;
  /* generate secret number: */
  for(int i = 0; i < pgm_info->height; i++){
    for(int j = 0; j < pgm_info->width; j++){
      random = (double) rand() / RAND_MAX;
      if(random < p){
        results[h++] = 1;//no anda poniendo 0
      }else if (random > q){
        results[h++] = 255;
      }else{
        results[h++] = pgm_info->pixels[i][j];
      }
    }
  }
  //print_results(results,pgm_info->height * pgm_info->width, false);
  create_new_picture(results, output, pgm_info);

}

double psnr(char* original, char* noisy){
  PGMInfo originalIMageInfo = parse_pgm(original,1);
  PGMInfo noisyIMageInfo = parse_pgm(noisy,1);

  double sum = 0;
  for(int i = 0; i < originalIMageInfo.height; i++){
    for(int j = 0; j < originalIMageInfo.width; j++){
      sum += pow((originalIMageInfo.pixels[i][j] - noisyIMageInfo.pixels[i][j]), 2);
    }
  }
  //printf("sum = %lf \n" , sum );
  double ecm = sum / ( originalIMageInfo.height * originalIMageInfo.width);
  //printf("ecm = %lf \n" , ecm);
  double psnr = 10 * log10((pow(originalIMageInfo.max,2) / ecm));

  return psnr;
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

  //TODO habria que ver si el results[i] > 255 => poner 255???? (sino pondria cualquier cosa)
  for(int i = 0; i < pgm_info->width * pgm_info->height; i++){
    sprintf(info, "%c" ,(unsigned char) (unsigned int) results[i]);
    fputs(info, outputFd);
  }
}
