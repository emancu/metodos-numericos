#include <tools.h>

int main(int argc, char* argv[]){
  static const char *optString = "f:";
  int c;
  string number_of_floors, floor_mass, light_car_mass, heavy_car_mass;
  char* input_path;

  while((c = getopt(argc, argv, optString)) != -1){
    switch(c){
      case 'f': { input_path  = optarg; break; }
      default:  { printf("Cannot parse.\n"); }
    }
  }

  parse_input(input_path);

  printf("\ntp3\n");

  return 0;
}
