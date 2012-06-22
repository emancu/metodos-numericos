#include <types.h>
#include <tools.h>
#include <matrix.h>

using namespace std;

void parse_input(char* input_path, Matrix* a){
  string floors, floor_mass_str, light_car_mass_str, heavy_car_mass_str, coeff, amount_light_cars, amount_heavy_cars;
  ifstream input;

  input.open(input_path, ifstream::in);
  input >> floors >> floor_mass_str >> light_car_mass_str >> heavy_car_mass_str;

  int number_of_floors = atoi(floors.c_str()); //Parse to int
  int floor_mass = atoi(floor_mass_str.c_str()); //Parse to int
  int light_car_mass = atoi(light_car_mass_str.c_str()); //Parse to int
  int heavy_car_mass = atoi(heavy_car_mass_str.c_str()); //Parse to int

  /*
  printf("number_floors = %s \n" ,floors.c_str());
  printf("floor_mas = %s \n" ,floor_mass_str.c_str());
  printf("Light = %s \n" , light_car_mass_str.c_str());
  printf("heavy_mas = %s \n" , heavy_car_mass_str.c_str());
  */

  int *light_cars_array, *heavy_cars_array, *floors_mass, *coefficients;
  light_cars_array = new int[number_of_floors];
  heavy_cars_array = new int[number_of_floors];
  coefficients = new int[number_of_floors];
  floors_mass = new int[number_of_floors];

  //leo los coeficientes
  for(int i = 0; i < number_of_floors ; i++){
    input >> coeff;
    coefficients[i] = atoi(coeff.c_str());
    //printf("coef piso %d = %d \n" , i,  atoi(coeff.c_str()));
  }

  //leo autos livianos por piso
  for(int i = 0; i < number_of_floors ; i++){
    input >> amount_light_cars;
    light_cars_array[i] = atoi(amount_light_cars.c_str());
    //printf("livianos piso %d = %d \n" , i,  atoi(amount_light_cars.c_str()));
  }

  //leo autos pesados por piso
  for(int i = 0; i < number_of_floors ; i++){
    input >> amount_heavy_cars;
    heavy_cars_array[i] = atoi(amount_heavy_cars.c_str());
    //printf("pesados piso %d = %d \n" , i,  atoi(amount_heavy_cars.c_str()));
  }

  //saco las masas de los pisos
  for(int i = 0; i < number_of_floors ; i++){
    //sumo la masa del piso (todas las mismas), el peso de los autos pesados, y los livianos
    floors_mass[i] = floor_mass + light_cars_array[i] * light_car_mass + heavy_cars_array[i] * heavy_car_mass;
    //printf("masa final piso %d = %d \n" , i,  floors_mass[i]);
  }


  a->rows = a->columns = number_of_floors;
  a->matrix = new double*[number_of_floors];

  // Fill matrix with zeroes.
  for(int i = 0; i < number_of_floors; i++){
    a->matrix[i] = new double[number_of_floors];
    for(int j = 0; j < number_of_floors; j++)
      a->matrix[i][j] = 0.0;
  }

  for(int i = 0; i < number_of_floors -1; i++){
    a->matrix[i][i+1] = coefficients[i+1] / floors_mass[i];
    a->matrix[i][i]   = (-coefficients[i] - coefficients[i+1]) / floors_mass[i];
    a->matrix[i+1][i] = coefficients[i+1] / floors_mass[i+1];
  }
  a->matrix[number_of_floors-1][number_of_floors-1] = -coefficients[number_of_floors-1] / floors_mass[number_of_floors-1];

  carvalues(a);
  // factorize_qr(a);

}

void carvalues(Matrix *a){
  pair<Matrix, Matrix> qr;
  int iteracion = 0;

  qr = factorize_qr(a);

  while(iteracion++ < 30)
    qr = factorize_qr( &multiplyMatrix( &qr.second, &qr.first));


  printf("Ter,omasdkla");
  print_matrix(&multiplyMatrix( &qr.second, &qr.first));

}

pair<Matrix, Matrix> factorize_qr(Matrix *m) {
  double a,b,c,norma, upper_band;
  Matrix q_t, r, p;

  clone_matrix(*m, &r);

  // Hago la identidad. TODO: Exportar
  p.rows = q_t.rows = p.columns = q_t.columns = r.rows;
  q_t.matrix = new double*[r.rows];
  p.matrix = new double*[r.rows];

  for(int i = 0; i < p.rows; i++){
    q_t.matrix[i] = new double[q_t.columns];
    p.matrix[i]   = new double[p.columns];
    for(int j = 0; j < p.columns; j++)
      q_t.matrix[i][j] = p.matrix[i][j] = 0.0;

    q_t.matrix[i][i] = p.matrix[i][i] = 1.0;
  }

  for(int row=0; row < r.rows - 1; row++) {
    a = r.matrix[row][row];
    b = r.matrix[row+1][row];
    c = r.matrix[row+1][row+2];
    upper_band = r.matrix[row][row+1];

    norma = sqrt( a*a + b*b);

    // Generamos P, a partir de la identidad
    p.matrix[row][row]     = a/norma;
    p.matrix[row][row+1]   = b/norma;
    p.matrix[row+1][row]   = -b/norma;
    p.matrix[row+1][row+1] = a/norma;

    r = multiplyMatrix(&p, &r);
    q_t = multiplyMatrix(&p, &q_t);

    // Restauramos la identidad en P
    p.matrix[row][row]   = p.matrix[row+1][row+1] = 1.0;
    p.matrix[row][row+1] = p.matrix[row+1][row] = 0.0;
  }

  transpose(&q_t);

  printf("-------\nA\n");
  print_matrix(m);

  printf("Q\n");
  print_matrix(&q_t);
  printf("R\n");
  print_matrix(&r);

  printf("QR\n");
  print_matrix(& multiplyMatrix(&q_t, &r));

  return make_pair(q_t, r);
}
