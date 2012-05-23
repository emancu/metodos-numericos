#include <types.h>
#include <tools.h>
#include <matrix.h>
#include <math.h>

#include <string.h>
using namespace std;

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

  string pict = (string) picture;
  string name = pict.substr(pict.find_last_of('/')+1);
  string nameWithoutExtension = name.substr(0,name.find_last_of('.'));
  sprintf(output, "%s%s_l%.1f_f%d.pgm", output, nameWithoutExtension.c_str(), lambda, factor);

  PGMInfo pgm_info = parse_pgm(picture,factor);
  printf("Generadno matriz... \n");
  Matrix matrix = build_matrix(lambda, &pgm_info);
  printf("Termino generacion... \n");
  double results[pgm_info.fHeight * pgm_info.fWidth];

  printf("Empiezo gauss ... \n");
  gauss(matrix, &pgm_info);
  solve_equations(matrix, &pgm_info, results);

  printf("TERMINE gauss ... \n");
  create_new_picture(results, output, &pgm_info);

  free_pixels_memory(&pgm_info);

  return 0;
}
