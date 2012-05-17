#include <types.h>
#include <tools.h>
#include <matrix.h>
#include <math.h>

int main(int argc, char* argv[]){
  static const char *optString = "o:f:p:q:";
  int c;
  char* picture;
  char* output;
  double p,q;

  while((c = getopt(argc, argv, optString)) != -1){
    switch(c){
      case 'f': { picture = optarg; break; }
      case 'o': { output = optarg; break; }
      case 'p': { p = atof(optarg); break; }
      case 'q': { q = atof(optarg); break; }
      default:  { printf("Cannot parse.\n"); }
    }
  }
  printf("p = %lf \n" , p );

  PGMInfo pgm_info = parse_pgm(picture,1);
  double results[pgm_info.height * pgm_info.width];
  createWithSaltPeperNoise(results, p, q, output, &pgm_info);

  free_pixels_memory(&pgm_info);
  return 0;
}
