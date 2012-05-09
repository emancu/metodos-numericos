#include <types.h>
#include <tools.h>
#include <matrix.h>

int main(int argc, char* argv[]){
  static const char *optString = "l:f:";
  int c;
  char* picture;
  double lambda;

  while((c = getopt(argc, argv, optString)) != -1){
    switch(c){
      case 'l': { lambda  = atof(optarg); break; }
      case 'f': { picture = optarg; break; }
      default:  { printf("Cannot parse.\n"); }
    }
  }

  LowerBands lower_bands;
  Matrix matrix = build_matrix(lambda, picture, &lower_bands);

  gauss(&matrix, &lower_bands);

  double results[matrix.size()];
  solve_equations(&matrix, results);

  print_results(results, matrix.size(), false);

  return 0;
}
