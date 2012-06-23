#include <matrix.h>

/*
 * Generators
 */

Matrix::Matrix() {
}

Matrix::Matrix(const Matrix &base) {
  _rows = base.rows();
  _cols = base.cols();

  _matrix = new double*[_rows];
  for(int i = 0; i < _rows; i++){
    _matrix[i] = new double[_cols];
    for(int j = 0; j < _cols; j++)
      _matrix[i][j] = base.get(i,j);
  }
}

Matrix::Matrix(int rows, int cols) {
  _rows    = rows;
  _cols = cols;

  _matrix = new double*[_rows];
  for(int i = 0; i < _rows; i++){
    _matrix[i] = new double[_cols];
  }
}

Matrix::~Matrix() {
  for(int i = 0; i < _rows; i++)
    delete [] _matrix[i];
  delete [] _matrix;
}

/*
 * Modifican self
 */

/*
 * Transforms self into identity matrix
 */
void Matrix::identity() {
  zero();
  for(int j = 0; j < _cols; j++)
    _matrix[j][j] = 1.0;
}

/*
 * Transforms self into 0 matrix
 */
void Matrix::zero() {
  for(int i = 0; i < _rows; i++)
    for(int j = 0; j < _cols; j++)
      _matrix[i][j] = 0.0;
}

/*
 * M * self.
 * Siempre son cuadradas y del mismo tamaño.
 * El resultado se guarda en self
 */
void Matrix::left_multiply_by(const Matrix &m) {
  Matrix *r = new Matrix(_rows, _cols);
  double aux;
  r->zero();

  for(int i = 0; i < _rows; i++) {
    for(int j = 0; j < _cols; j++) {
      aux = 0;
      for(int k = 0; k < _cols; k++)
        aux += m.get(i,k) * _matrix[k][j];

      r->set(i,j, aux);
    }
  }

  delete _matrix;       //Free old matrix
  _matrix = r->_matrix; //Copy results
}

/*
 * self * M
 * Siempre son cuadradas y del mismo tamaño.
 * El resultado se guarda en self
 */
void Matrix::right_multiply_by(const Matrix &m) {
  Matrix *r = new Matrix(_rows, _cols);
  double aux;
  r->zero();

  for(int i = 0; i < _rows; i++) {
    for(int j = 0; j < _cols; j++) {
      aux = 0;
      for(int k = 0; k < _cols; k++)
        aux += _matrix[i][k] * m.get(k,j);

      r->set(i,j, aux);
    }
  }

  delete _matrix;       //Free old matrix
  _matrix = r->_matrix; //Copy results
}

void Matrix::transpose() {
  double aux;
  for(int i = 0; i < _cols; i++){
    for(int j = i+1; j < _rows; j++){
      aux = _matrix[i][j];
      _matrix[i][j] = _matrix[j][i];
      _matrix[j][i] = aux;
    }
  }
}

void Matrix::set(int r, int c, double v) {
  _matrix[r][c] = v;
}

/*
 * NO modifican self
 */

double Matrix::get(int r, int c) const {
  return _matrix[r][c];
}

int Matrix::cols() const {
  return _cols;
}

int Matrix::rows() const {
  return _rows;
}

void Matrix::print() const {
  cout << _rows << "x" << _cols << endl;
  for(int i = 0; i < _rows; i++){
    for(int j = 0; j < _cols; j++)
      printf("%12.4lf" , _matrix[i][j]);

    cout << endl;
  }
  cout << endl << endl;
}

double* Matrix::diagonal() const {
  double *diagonal = new double[_rows];
  for(int i=0; i < _rows; i++)
    diagonal[i] = _matrix[i][i];

  return diagonal;
}

double Matrix::sum_lower_triangular() const {
  double sum = 0;

  for(int i=1; i < _rows; i++)
    for(int j=0; j < i; j++)
      sum += abs(_matrix[i][j]);

  return sum;
}
