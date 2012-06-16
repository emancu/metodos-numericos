#include <types.h>
#include <tools.h>
#include <matrix.h>

void parse_input(char* input_path, Matrix* a){
  string number_of_floors, floor_mass, light_car_mass, heavy_car_mass;
  ifstream input;

  input.open(input_path, ifstream::in);
  input >> number_of_floors >> floor_mass >> light_car_mass >> heavy_car_mass;

  Matrix m, k;
  m.rows    = atoi(number_of_floors.c_str()); // Parses to int.
  m.columns = m.rows;
  k.rows    = m.rows;
  k.columns = m.columns;
}

