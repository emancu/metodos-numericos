#include <building.h>

/*
 * Generators
 */

Building::Building() {
}

Building::Building(const Building& base) {
  _floors         = base._floors;
  _floor_mass     = base._floor_mass;
  _light_car_mass = base._light_car_mass;
  _heavy_car_mass = base._heavy_car_mass;

  _light_cars_amount = base._light_cars_amount;
  _heavy_cars_amount = base._heavy_cars_amount;

  _light_cars_stack = base._light_cars_stack;
  _light_car_to     = base._light_car_to;
  _heavy_cars_stack = base._heavy_cars_stack;
  _heavy_car_to     = base._heavy_car_to;

  _light_cars_array    = new int[_floors];
  _heavy_cars_array    = new int[_floors];
  _coefficients        = new int[_floors];
  _natural_frequencies = new double[_floors];

  // copio los coeficientes.
  for(int i = 0; i < _floors ; i++)
    _coefficients[i] = base._coefficients[i];

  // copio autos livianos por piso.
  for(int i = 0; i < _floors ; i++)
    _light_cars_array[i] = base._light_cars_array[i];

  // copio autos pesados por piso.
  for(int i = 0; i < _floors ; i++)
    _heavy_cars_array[i] = base._heavy_cars_array[i];

  // copio frecuencias naturales.
  for(int i = 0; i < _floors ; i++)
    _natural_frequencies[i] = base._natural_frequencies[i];

  _matrix = new Matrix(*(base.matrix()));
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

  _light_cars_stack = 0;
  _light_car_to     = 0;
  _heavy_cars_stack = 0;
  _heavy_car_to     = 0;

  _light_cars_array    = new int[_floors];
  _heavy_cars_array    = new int[_floors];
  _coefficients        = new int[_floors];
  _natural_frequencies = new double[_floors];

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
  delete[] _light_cars_array;
  delete[] _heavy_cars_array;
  delete[] _coefficients;
  delete[] _natural_frequencies;
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

  int moves = rand() % (50) + _floors;

  // Limpio los arrays
  for(int i = 0; i < _floors ; i++){
    _light_cars_array[i] = 0;
    _heavy_cars_array[i] = 0;
  }

  int i;
  while(moves-- && amount_light) {
    i = rand() % _floors;
    if(_light_cars_array[i] == 0) {
      _light_cars_array[i] = rand() % (amount_light+1);
      amount_light -= _light_cars_array[i];
    }
  }

  moves = rand() % (50) + _floors;
  while(moves-- && amount_heavy ) {
    i = rand() % (_floors);
    if(_heavy_cars_array[i] == 0) {
      _heavy_cars_array[i] = rand() % (amount_heavy+1);
      amount_heavy -= _heavy_cars_array[i];
    }
  }

  i = rand() % _floors;
  _light_cars_array[i] += amount_light;

  i = rand() % _floors;
  _heavy_cars_array[i] += amount_heavy;

  // Check integrity
  int auxl = 0, auxh = 0;
  for(i=0; i < _floors; i++){
    auxl += _light_cars_array[i];
    auxh += _heavy_cars_array[i];
  }

  if(auxl != _light_cars_amount || auxh != _heavy_cars_amount) {
    cout << "Mal los light" << auxl << " as " << _light_cars_amount << endl;
    cout << "Mal los heavy" << auxh << " as " << _heavy_cars_amount << endl;
    exit(1);
  }

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
  }

  if(_heavy_cars_array[floor_j] > 0){
    _heavy_cars_array[floor_j]--;
    _heavy_cars_array[floor_i]++;
  }
}

void Building::move_heavy_car() {
  if(_heavy_cars_amount > 0){
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
  }
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
  }
}

void Building::natural_frequencies(double* eigenvalues) {
  for(int i=0; i < _floors; i++)
    _natural_frequencies[i] = sqrt(-eigenvalues[i]);
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

int Building::distance_to(const Building& building) const {
  int differences_light = 0;
  int differences_heavy = 0;

  for(int i = 0; i < _floors; i++){
    differences_light += (int) abs(_light_cars_array[i] - building._light_cars_array[i]);
    differences_heavy += (int) abs(_heavy_cars_array[i] - building._heavy_cars_array[i]);
  }

  return ((differences_light + differences_heavy) / 2);
}

bool Building::is_safe() const {
  for(int i=0; i < _floors; i++)
    if(frequency_in_range(_natural_frequencies[i])) return false;
  return true;
  // Alternative implementation?
  // return frequencies_in_range() == 0;
}

int Building::frequencies_in_range() const {
  int result = 0;
  for(int i=0; i < _floors; i++)
    if(frequency_in_range(_natural_frequencies[i])) result++;
  return result;
}

bool Building::operator== (const Building& base) const {
  bool result = _floors            == base._floors            &&
                _floor_mass        == base._floor_mass        &&
                _light_car_mass    == base._light_car_mass    &&
                _heavy_car_mass    == base._heavy_car_mass    &&
                _light_cars_amount == base._light_cars_amount &&
                _heavy_cars_amount == base._heavy_cars_amount;

  for(int i = 0; i < _floors ; i++)
    result = result && _coefficients[i] == base._coefficients[i];

  for(int i = 0; i < _floors ; i++)
    result = result && _heavy_cars_array[i] == base._heavy_cars_array[i];

  for(int i = 0; i < _floors ; i++)
    result = result && _light_cars_array[i] == base._light_cars_array[i];

  for(int i = 0; i < _floors ; i++)
    result = result && _natural_frequencies[i] == base._natural_frequencies[i];

  return result;
}

bool Building::same_number_of_cars(const Building& base) const {
  int auxl = 0, auxh = 0;
  for(int i=0; i < _floors; i++){
    auxl += _light_cars_array[i];
    auxh += _heavy_cars_array[i];
  }

  int auxl_base = 0, auxh_base = 0;
  for(int i=0; i < _floors; i++){
    auxl_base += base._light_cars_array[i];
    auxh_base += base._heavy_cars_array[i];
  }

  return auxl_base == auxl && auxh_base == auxh;
}

/*
 * Getters
 */

int Building::amount_light_cars() const {
  return _light_cars_amount;
}

int Building::amount_heavy_cars() const {
  return _heavy_cars_amount;
}

int Building::floors() const {
  return _floors;
}

/*
 * Helpers
 */

bool Building::frequency_in_range(double frequency) const {
  return (2.7 <= frequency && frequency <= 3.3);
}
