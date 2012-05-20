#include <types.h>
#include <matrix.h>
#include <tools.h>
#include <math.h>

double psnr(char* original, char* noisy);

int main(int argc, char* argv[]){
  static const char *optString = "n:c:";
  int c;
  char *with_noise, *without_noise;

  while((c = getopt(argc, argv, optString)) != -1){
    switch(c){
      case 'n': { with_noise = optarg; break; }
      case 'c': { without_noise = optarg; break; }
      default:  { printf("Cannot parse.\n"); }
    }
  }

  printf(" PSNR: %.6lf ", psnr(without_noise, with_noise));

  return 0;
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
