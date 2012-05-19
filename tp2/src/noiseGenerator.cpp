#include <tools.h>
#include <time.h>
#include <math.h>
#include <noiseGenerator.h>




void createWithSaltPeperNoise(double * results, double p, double q, char* output, PGMInfo* pgm_info){
  /* initialize random seed: */
  double random;
  srand ( 0 );

  int h = 0;
  /* generate secret number: */
  for(int i = 0; i < pgm_info->height; i++){
    for(int j = 0; j < pgm_info->width; j++){
      //GENERAR RUIDO GAUSSIANO : CON EL MISMO RANDOM MULTIPLICARLO POR UNA CONSTANTE - entre 0 y 255 - Y DPS SATURAR LA IMAGEN
      //FIJARNOS QUE RANDOM QUEDE ENTRE -1 y 1 PARA SUMAR Y RESTAR... O SEA NO SIEMPRE SUMAR
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

void createGaussianNoise(double * results, int factor, char* output, PGMInfo* pgm_info){
  /* initialize random seed: */
  double random;
  srand ( 0 );

  int h = 0;
  /* generate secret number: */
  for(int i = 0; i < pgm_info->height; i++){
    for(int j = 0; j < pgm_info->width; j++){
      random = (2 * (double) rand() / RAND_MAX) - 1;
      results[h] = pgm_info->pixels[i][j] + random * factor ;
      results[h] = min((pgm_info->pixels[i][j] + random * factor), 255.0) ;
      results[h++] = max((pgm_info->pixels[i][j] + random * factor), 0.0) ;
    }
  }
  //print_results(results, pgm_info, false);

  //print_results(results,pgm_info->height * pgm_info->width, false);
  create_new_picture(results, output, pgm_info);
}

