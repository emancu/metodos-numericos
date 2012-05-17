#include <types.h>
#include <tools.h>
#include <matrix.h>
#include <math.h>

int main(int argc, char* argv[]){
  static const char *optString = "o:f:p:q:";
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
