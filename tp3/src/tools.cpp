#include <types.h>
#include <tools.h>
#include <matrix.h>

void parse_input(char* input_path, Matrix* a){
  string floors, floor_mass_str, light_car_mass_str, heavy_car_mass_str, coeff, amount_light_cars, amount_heavy_cars;
  ifstream input;

  input.open(input_path, ifstream::in);
  input >> floors >> floor_mass_str >> light_car_mass_str >> heavy_car_mass_str;

  int number_of_floors = atoi(floors.c_str()); //Parse to int
  int floor_mass = atoi(floor_mass_str.c_str()); //Parse to int
  int light_car_mass = atoi(light_car_mass_str.c_str()); //Parse to int
  int heavy_car_mass = atoi(heavy_car_mass_str.c_str()); //Parse to int

  printf("number_floors = %s \n" ,floors.c_str());
  printf("floor_mas = %s \n" ,floor_mass_str.c_str());
  printf("Light = %s \n" , light_car_mass_str.c_str());
  printf("heavy_mas = %s \n" , heavy_car_mass_str.c_str());

  int *light_cars_array, *heavy_cars_array, *floors_mass, *coefficients;
  light_cars_array = new int[number_of_floors];
  heavy_cars_array = new int[number_of_floors];
  coefficients = new int[number_of_floors];
  floors_mass = new int[number_of_floors];

  //leo los coeficientes
  for(int i = 0; i < number_of_floors ; i++){
    input >> coeff;
    coefficients[i] = atoi(coeff.c_str());
    printf("coef piso %d = %d \n" , i,  atoi(coeff.c_str()));
  }

  //leo autos livianos por piso
  for(int i = 0; i < number_of_floors ; i++){
    input >> amount_light_cars;
    light_cars_array[i] = atoi(amount_light_cars.c_str());
    printf("livianos piso %d = %d \n" , i,  atoi(amount_light_cars.c_str()));
  }

  //leo autos pesados por piso
  for(int i = 0; i < number_of_floors ; i++){
    input >> amount_heavy_cars;
    heavy_cars_array[i] = atoi(amount_heavy_cars.c_str());
    printf("pesados piso %d = %d \n" , i,  atoi(amount_heavy_cars.c_str()));
  }

  //saco las masas de los pisos
  for(int i = 0; i < number_of_floors ; i++){
    //sumo la masa del piso (todas las mismas), el peso de los autos pesados, y los livianos
    floors_mass[i] = floor_mass + light_cars_array[i] * light_car_mass + heavy_cars_array[i] * heavy_car_mass;
    printf("masa final piso %d = %d \n" , i,  floors_mass[i]);
  }


  a->rows = a->columns = number_of_floors;

  int row_amount = 3;
  int matrix_width = number_of_floors;
  a->matrix = new double*[row_amount];

  // Fill matrix with zeroes.
  for(int i = 0; i < row_amount; i++){
    a->matrix[i] = new double[matrix_width];
    for(int j = 0; j < matrix_width; j++)
      a->matrix[i][j] = 0.0;
  }

  //lleno la matriz y la multiplico por la inversa de A
  for(int i = 0; i < matrix_width; i++){
    if( i < matrix_width - 1){
      a->matrix[0][i] = coefficients[i+1] / floors_mass[i];
      a->matrix[1][i] = (-coefficients[i] - coefficients[i + 1]) / floors_mass[i];
    }else{
      a->matrix[1][i] = -coefficients[i] / floors_mass[i];
    }
    a->matrix[2][i+1] = coefficients[i+1] / floors_mass[i];
  }

  print_matrix(a);

  Matrix m, k;
  m.rows    = number_of_floors;
  m.columns = m.rows;
  k.rows    = m.rows;
  k.columns = m.columns;
}

