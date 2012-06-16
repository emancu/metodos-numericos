#include <types.h>
#include <tools.h>

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

  Matrix a;
  parse_input(input_path, &a);

  printf("\ntp3\n");

  return 0;
}
