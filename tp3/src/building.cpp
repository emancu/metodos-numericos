#include <building.h>

/*
 * Generators
 */

Building::Building() {
}

Building::Building(char *input_path) {
  string floors, floor_mass_str, light_car_mass_str, heavy_car_mass_str, coeff, amount_light_cars, amount_heavy_cars;
  ifstream input;

  input.open(input_path, ifstream::in);
  input >> floors >> floor_mass_str >> light_car_mass_str >> heavy_car_mass_str;

  _floors         = atoi(floors.c_str());
  _floor_mass     = atoi(floor_mass_str.c_str());
  _light_car_mass = atoi(light_car_mass_str.c_str());
  _heavy_car_mass = atoi(heavy_car_mass_str.c_str());

  _light_cars_amount = 0;
  _heavy_cars_amount = 0;
  _moves = 0;

  _light_cars_stack = 0;
  _light_car_to     = 0;
  _heavy_cars_stack = 0;
  _heavy_car_to     = 0;

  _light_cars_array = new int[_floors];
  _heavy_cars_array = new int[_floors];
  _coefficients = new int[_floors];


  //leo los coeficientes
  for(int i = 0; i < _floors ; i++){
    input >> coeff;
    _coefficients[i] = atoi(coeff.c_str());
  }

  //leo autos livianos por piso
  for(int i = 0; i < _floors ; i++){
    input >> amount_light_cars;
    _light_cars_array[i] = atoi(amount_light_cars.c_str());
    _light_cars_amount += _light_cars_array[i];
  }

  //leo autos pesados por piso
  for(int i = 0; i < _floors ; i++){
    input >> amount_heavy_cars;
    _heavy_cars_array[i] = atoi(amount_heavy_cars.c_str());
    _heavy_cars_amount += _heavy_cars_array[i];
  }

  generate_matrix();
}

Building::~Building() {
  delete _light_cars_array;
  delete _heavy_cars_array;
  delete _coefficients;
  delete _matrix;
}


/*
 * Modifican self
 */

void Building::generate_matrix() {
  int *floors_mass = new int[_floors];

  //saco las masas de los pisos
  for(int i = 0; i < _floors ; i++)
    //sumo la masa del piso (todas las mismas), el peso de los autos pesados, y los livianos
    floors_mass[i] = _floor_mass + _light_cars_array[i] * _light_car_mass + _heavy_cars_array[i] * _heavy_car_mass;

  if(_matrix) delete _matrix;
  _matrix = new Matrix(_floors, _floors);
  _matrix->zero();

  for(int i = 0; i < _floors -1; i++){
    _matrix->set(i, i+1, _coefficients[i+1] / floors_mass[i]);
    _matrix->set(i,   i, (-_coefficients[i] - _coefficients[i+1]) / floors_mass[i]);
    _matrix->set(i+1, i, _coefficients[i+1] / floors_mass[i+1]);
  }
  _matrix->set(_floors-1, _floors-1, -_coefficients[_floors-1] / floors_mass[_floors-1]);

  delete[] floors_mass;
}

void Building::randomize() {
  int amount_light = _light_cars_amount;
  int amount_heavy = _heavy_cars_amount;
  srand(time(NULL));

  for(int i=0; i< _floors-1; i++) {
    _light_cars_array[i] = rand() % (amount_light+1);
    _heavy_cars_array[i] = rand() % (amount_heavy+1);

    amount_light -= _light_cars_array[i];
    amount_heavy -= _heavy_cars_array[i];
  }

  _light_cars_array[_floors-1] = amount_light;
  _heavy_cars_array[_floors-1] = amount_heavy;

}

void Building::swap_or_move_heavy_light_cars() {
  srand(time(NULL));

  int floor_i = rand() % _floors;
  int floor_j = rand() % _floors;

  // In case the floors are the same.
  while(floor_i == floor_j || (_light_cars_array[floor_i] == 0 && _heavy_cars_array[floor_j] == 0)){
    floor_i = rand() % _floors;
    floor_j = rand() % _floors;
  }

  if(_light_cars_array[floor_i] > 0){
    _light_cars_array[floor_i]--;
    _light_cars_array[floor_j]++;
    _moves++;
  }

  if(_heavy_cars_array[floor_j] > 0){
    _heavy_cars_array[floor_j]--;
    _heavy_cars_array[floor_i]++;
    _moves++;
  }
}

void Building::move_heavy_car() {
  srand(time(NULL));

  int floor_i = rand() % _floors;
  int floor_j = rand() % _floors;

  // In case the floors are the same.
  while(floor_i == floor_j || _heavy_cars_array[floor_i] == 0){
    floor_i = rand() % _floors;
    floor_j = rand() % _floors;
  }

  _heavy_cars_array[floor_i]--;
  _heavy_cars_array[floor_j]++;
  _moves++;
}

void Building::move_all_light_cars(){
  if(_light_cars_stack == _floors - 1){
    cout << "move_all_light_cars: no hubo suerte, usando move_heavy_car()" << endl;
    this->move_heavy_car();
  }else if(_light_cars_stack == 0 && _light_car_to == 0){
    for(int i = 0; i < _floors; i++)
      _light_cars_array[i] = 0;

    _light_cars_array[_light_cars_stack] = _light_cars_amount;
    _light_car_to = 1;
  }else{
    _light_cars_array[_light_cars_stack]--;
    if(_light_cars_array[_light_cars_stack] == 0)
      _light_cars_stack++;

    _light_cars_array[_light_car_to]++;
    if(_light_car_to == _floors - 1)
      _light_car_to = _light_cars_stack + 1;
    else
      _light_car_to++;

    _moves++;
  }
}

void Building::move_all_heavy_cars(){
  if(_heavy_cars_stack == _floors - 1){
    cout << "move_all_heavy_cars: no hubo suerte, usando move_heavy_car()" << endl;
    this->move_heavy_car();
  }else if(_heavy_cars_stack == 0 && _heavy_car_to == 0){
    for(int i = 0; i < _floors; i++)
      _heavy_cars_array[i] = 0;

    _heavy_cars_array[_heavy_cars_stack] = _heavy_cars_amount;
    _heavy_car_to = 1;
  }else{
    _heavy_cars_array[_heavy_cars_stack]--;
    if(_heavy_cars_array[_heavy_cars_stack] == 0)
      _heavy_cars_stack++;

    _heavy_cars_array[_heavy_car_to]++;
    if(_heavy_car_to == _floors - 1)
      _heavy_car_to = _heavy_cars_stack + 1;
    else
      _heavy_car_to++;

    _moves++;
  }
}
/*
 * NO modifican self
 */

Matrix* Building::matrix() const {
  return _matrix;
}

void Building::print() const {
  cout << "------------------------ Building ------------------------" << endl;
  cout << "Number of floors: " << _floors << endl;
  cout << "Floor mass: " << _floor_mass << endl;
  cout << "Light car mass: " << _light_car_mass << "  Heavy car mass: " << _heavy_car_mass << endl;
  cout << "Light car amount: " << _light_cars_amount << " Heavy car amount: " << _heavy_cars_amount << endl;
  cout << "Number of moves: " << _moves << endl;

  cout << endl << "Cars" << endl << "L ";
  int aux = 0;
  for(int i=0; i < _floors; i++) {
    printf("%4.0d", _light_cars_array[i]);
    aux += _light_cars_array[i];
  }

  cout << " => " << aux << endl << "H ";
  aux = 0;
  for(int i=0; i < _floors; i++) {
    printf("%4.0d", _heavy_cars_array[i]);
    aux += _heavy_cars_array[i];
  }

  cout << " => " << aux << endl;
  cout << "------------------------ ******** ------------------------" << endl;
}

void Building::output_file(char* output_path) const {
  ofstream file;
  file.open(output_path);

  file << _floors << " " << _floor_mass << " " << _light_car_mass << " " << _heavy_car_mass << endl;

  for(int i = 0; i < _floors; i++){
    file << _coefficients[i];
    if(i == _floors - 1)
      file << endl;
    else
      file << " ";
  }

  for(int i = 0; i < _floors; i++){
    file << _light_cars_array[i];
    if(i == _floors - 1)
      file << endl;
    else
      file << " ";
  }

  for(int i = 0; i < _floors; i++){
    file << _heavy_cars_array[i];
    if(i == _floors - 1)
      file << endl;
    else
      file << " ";
  }

  file.close();
}

