#include <tools.h>
#include <matrix.h>

int main(int argc, char* argv[]){
  static const char *optString = "f:";
  int c;
  char* input_path;

  while((c = getopt(argc, argv, optString)) != -1){
    switch(c){
      case 'f': { input_path  = optarg; break; }
      default:  { printf("Cannot parse.\n"); }
    }
  }

  Matrix *a = parse_input(input_path);

  // Aplico algoritmo QR
  carvalues(*a);


  delete a;
  return 0;
}
