#include <tools.h>

double* eigenvalues(const Matrix &a, double epsilon, int iterations) {
  double prev_sum=0, cur_sum=0;
  Matrix *q = new Matrix(a.rows(), a.cols());
  Matrix *r = new Matrix(a);

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

void random_heuristic(Building* building, int epsilon, int iterations){
  Matrix *a = building->matrix();

  // Aplico algoritmo QR
  double *values;

  values = eigenvalues(*a, epsilon, iterations);
  natural_frecuencies(values, a->rows());

  while(!is_building_safe(values, a->rows())){

    building->randomize();
    building->generate_matrix();
    a = building->matrix();

    values = eigenvalues(*a, epsilon, iterations);
    natural_frecuencies(values, a->rows());

    //cout << is_building_safe(values, a->rows()) << endl;
  }

  delete values;
}

void swap_or_move_heuristic(Building* building, int epsilon, int iterations){
  Matrix *a = building->matrix();

  // Aplico algoritmo QR
  double *values;

  values = eigenvalues(*a, epsilon, iterations);
  natural_frecuencies(values, a->rows());

  while(!is_building_safe(values, a->rows())){
    building->swap_or_move_heavy_light_cars();
    building->generate_matrix();
    a = building->matrix();

    values = eigenvalues(*a, epsilon, iterations);
    natural_frecuencies(values, a->rows());

    //cout << is_building_safe(values, a->rows()) << endl;
  }

  delete values;
}

void print_array(double* array, int size) {
  for(int i=0; i < size; i++)
    cout << array[i] << " ";

  cout << endl;
}
