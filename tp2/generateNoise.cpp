#include <types.h>
#include <tools.h>
#include <noiseGenerator.h>
#include <matrix.h>
#include <math.h>

int main(int argc, char* argv[]){
  static const char *optString = "M:o:f:p:q:r:";
  int c, method, factor;
  char* picture;
  char* output;
  double p,q;

  while((c = getopt(argc, argv, optString)) != -1){
    switch(c){
      case 'M': { method = atoi(optarg); break; }
      case 'f': { picture = optarg; break; }
      case 'o': { output = optarg; break; }
      case 'p': { p = atof(optarg); break; }
      case 'q': { q = atof(optarg); break; }
      case 'r': { factor = atoi(optarg); break; }

      default:  { printf("Cannot parse.\n"); }
    }
  }
  printf("p = %lf \n" , p );

  PGMInfo pgm_info = parse_pgm(picture,1);
  double results[pgm_info.height * pgm_info.width];
  if(method==0)
    sprintf(output, "%s_salt_p%f_q%f.pgm", output, p, q);
  else
    sprintf(output, "%s_gauss_f%d.pgm", output, factor);

  switch(method) {
    case 0:  { printf("Salt: \n");      createWithSaltPeperNoise(results, p, q, output, &pgm_info);   break; }
    case 1:  { printf("gaussian:\n");   createGaussianNoise(results, factor, output, &pgm_info); break; }
    default: { printf("Metodo no valido.\n"); }
  }


  free_pixels_memory(&pgm_info);
  return 0;
}
