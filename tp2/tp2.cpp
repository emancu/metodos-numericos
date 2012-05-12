#include <types.h>
#include <tools.h>
#include <matrix.h>

int main(int argc, char* argv[]){
  static const char *optString = "l:f:v";
  int c;
  char* picture;
  double lambda;
  bool verification = false;

  while((c = getopt(argc, argv, optString)) != -1){
    switch(c){
      case 'l': { lambda  = atof(optarg); break; }
      case 'f': { picture = optarg; break; }
      case 'v': { verification = true; break; }
      default:  { printf("Cannot parse.\n"); }
    }
  }

  printf("BUILDING MATRIX...");
  LowerBands lower_bands;
  Matrix matrix = build_matrix(lambda, picture, &lower_bands);
  printf("DONE\nSTARTING GAUSS...");

  gauss(&matrix, &lower_bands);
  printf("DONE\nSOLVING EQUATIONS...");

  double results[matrix.size()];
  solve_equations(&matrix, results);
  printf("DONE\n");

  //print_matrix(&matrix);
  //print_results(results, matrix.size(), verification);

  return 0;
}
