#ifndef __TYPES__
#define __TYPES__

#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

typedef struct mtx {
  int rows;
  int columns;
  double** matrix;
} Matrix;

#endif
