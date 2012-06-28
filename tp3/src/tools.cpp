#include <tools.h>

double* eigenvalues(const Matrix &a, double epsilon, int iterations) {
  double prev_sum=0, cur_sum=0;
  Matrix *q = new Matrix(a.rows(), a.cols());
  Matrix *r = new Matrix(a);

  double* prev_diag = new double[r->rows() - 1];
  for(int i=0; i < r->rows() - 1; i++)
    prev_diag[i] = 0;

  double* cur_diag = r->sub_diagonal();

  cur_sum = r->sum_lower_triangular();

  while( stop_criteria_only_sub_diagonal(r->rows(), cur_diag, prev_diag, epsilon) && --iterations) {
    prev_sum = cur_sum;
    for(int i=0; i < r->rows() - 1; i++)
      prev_diag[i] = cur_diag[i];


    q->identity();
    qr_decomposition(q, r);

    // Calculo la proxima matriz base para la iteracion.
    r->right_multiply_by(*q);
    cur_sum = r->sum_lower_triangular();
    cur_diag = r->sub_diagonal();
  }


  if(!iterations) cout << "Sali por ITERACIONES" << endl;

  double *diagonal = r->diagonal();
  delete r;
  delete q;

  return diagonal;
}

bool stop_criteria_only_sub_diagonal(int size, double* cur,double* prev, double epsilon ){
  for(int i=0; i < size -1; i++)
    if(abs(cur[i] - prev[i]) > epsilon)
      return true;
  return false;
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

void print_array(double* array, int size) {
  for(int i=0; i < size; i++)
    //cout << array[i] << " ";
    printf("%4.5lf ", array[i]);

  cout << endl;
}
