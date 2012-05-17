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

  // printf("BUILDING MATRIX...");
  PGMInfo pgm_info = parse_pgm(picture);
  Matrix matrix = build_matrix(lambda, &pgm_info);
  // print_pretty_matrix(matrix, &pgm_info);
  // printf("DONE\nSTARTING GAUSS...");
  double results[pgm_info.height * pgm_info.width];
  //createWithSaltPeperNoise(results, 0.05, 0.95, output, &pgm_info);
  //double psnrValue = psnr(picture, output);
  //printf("el psnr es = %lf \n" , psnrValue);

  gauss(matrix, &pgm_info);
  // print_pretty_matrix(matrix, &pgm_info);
  // printf("DONE\nSOLVING EQUATIONS...");


  solve_equations(matrix, &pgm_info, results);
  // printf("DONE\n");

  // print_pretty_matrix(matrix, &pgm_info);
  //print_results(results, pgm_info.height * pgm_info.width, verification);
  create_new_picture(results, output, &pgm_info);

  free_pixels_memory(&pgm_info);

  return 0;
}
