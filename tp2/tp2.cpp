#include <types.h>
#include <tools.h>
#include <matrix.h>
#include <math.h>

int main(int argc, char* argv[]){
  static const char *optString = "o:l:f:r:";
  int c;
  char* picture;
  char* output;
  double lambda;
  int factor;

  while((c = getopt(argc, argv, optString)) != -1){
    switch(c){
      case 'l': { lambda  = atof(optarg); break; }
      case 'f': { picture = optarg; break; }
      case 'o': { output = optarg; break; }
      case 'r': { factor = atoi(optarg); break; }
      default:  { printf("Cannot parse.\n"); }
    }
  }

  PGMInfo pgm_info = parse_pgm(picture,factor);
  Matrix matrix = build_matrix(lambda, &pgm_info);
  double results[pgm_info.fHeight * pgm_info.fWidth];

  gauss(matrix, &pgm_info);
  solve_equations(matrix, &pgm_info, results);
  create_new_picture(results, output, &pgm_info);

  free_pixels_memory(&pgm_info);

  return 0;
}
