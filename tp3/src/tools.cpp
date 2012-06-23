#include <tools.h>

Matrix* parse_input(char* input_path) {
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

  Matrix *a = new Matrix(number_of_floors, number_of_floors);
  a->zero();

  for(int i = 0; i < number_of_floors -1; i++){
    a->set(i, i+1, coefficients[i+1] / floors_mass[i]);
    a->set(i,   i, (-coefficients[i] - coefficients[i+1]) / floors_mass[i]);
    a->set(i+1, i, coefficients[i+1] / floors_mass[i+1]);
  }
  a->set(number_of_floors-1, number_of_floors-1, -coefficients[number_of_floors-1] / floors_mass[number_of_floors-1]);

  delete light_cars_array;
  delete heavy_cars_array;
  delete floors_mass;
  delete coefficients;

  return a;
}

double* eigenvalues(const Matrix &a, double epsilon, int iterations) {
  double prev_sum=0, cur_sum=0;
  Matrix *q = new Matrix(a.rows(), a.cols());
  Matrix *r = new Matrix(a);

  cout << "-----------" << endl << "A" << endl;
  // a.print();
  cur_sum = r->sum_lower_triangular();

  while( abs(cur_sum - prev_sum) > epsilon && --iterations) {
    prev_sum = cur_sum;

    q->identity();
    qr_decomposition(q, r);

    // Calculo la proxima matriz base para la iteracion.
    r->right_multiply_by(*q);
    cur_sum = r->sum_lower_triangular();
  }

  if(!iterations) cout << "Sali por ITERACIONES" << endl;

  // cout << "RQ" << endl;
  // r->print();

  cout << "Termino la factorizacion." << endl;

  double *diagonal = r->diagonal();
  delete r;
  delete q;

  return diagonal;
}

void natural_frecuencies(double *eigenvalues, int size) {
  for(int i=0; i < size; i++)
    eigenvalues[i] = sqrt(-eigenvalues[i]);
}

bool is_building_safe(double *eigenvalues, int size) {
  for(int i=0; i < size; i++)
    if(2.7 <= eigenvalues[i] && eigenvalues[i] <= 3.3)
      return false;
  return true;
}

void qr_decomposition(Matrix *q_t, Matrix *r) {
  double a,b,c,norm, upper_band;
  Matrix *p = new Matrix(r->rows(), r->cols());
  p->identity();

  for(int row=0; row < r->rows() - 1; row++) {
    a = r->get(row,row);
    b = r->get(row+1,row);
    c = r->get(row+1,row+2);
    upper_band = r->get(row,row+1);

    norm = sqrt(a*a + b*b);

    // Generamos P, a partir de la identidad
    p->set(row,  row,    a/norm);
    p->set(row,  row+1,  b/norm);
    p->set(row+1,row,   -b/norm);
    p->set(row+1,row+1,  a/norm);

    r->left_multiply_by(*p);
    q_t->left_multiply_by(*p);

    // Restauramos la identidad en P
    p->set(row,  row,   1.0);
    p->set(row+1,row+1, 1.0);
    p->set(row,  row+1, 0.0);
    p->set(row+1,row,   0.0);
  }

  q_t->transpose();

  delete p;
}
