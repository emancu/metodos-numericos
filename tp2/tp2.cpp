#include <types.h>
#include <tools.h>
#include <matrix.h>
#include <math.h>

int main(int argc, char* argv[]){
  static const char *optString = "o:l:f:v";
  int c;
  char* picture;
  char* output;
  double lambda;
  bool verification = false;


  while((c = getopt(argc, argv, optString)) != -1){
    switch(c){
      case 'l': { lambda  = atof(optarg); break; }
      case 'f': { picture = optarg; break; }
      case 'v': { verification = true; break; }
      case 'o': { output = optarg; break; }
      default:  { printf("Cannot parse.\n"); }
    }
  }

  printf("BUILDING MATRIX...");
  LowerBands lower_bands;
  PGMInfo pgm_info = parse_pgm(picture);
  Matrix matrix = build_matrix(lambda, &pgm_info, &lower_bands);
  printf("DONE\nSTARTING GAUSS...");

  gauss(&matrix, &lower_bands);
  printf("DONE\nSOLVING EQUATIONS...");

  double results[matrix.size()];
  solve_equations(&matrix, results);
  printf("DONE\n");

  //print_pretty_matrix(&matrix);
  create_new_picture(results,output, (int) sqrt(matrix.size()));
  //print_results(results, matrix.size(), verification);

  free_pixels_memory(&pgm_info);
  return 0;
}
