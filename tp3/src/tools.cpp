#include <tools.h>

void parse_input(char* input_path){
  string number_of_floors, floor_mass, light_car_mass, heavy_car_mass;
  ifstream input;

  input.open(input_path, ifstream::in);
  input >> number_of_floors >> floor_mass >> light_car_mass >> heavy_car_mass;
}
