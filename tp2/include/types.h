#ifndef __TYPES__
#define __TYPES__
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <map>
#include <set>

using namespace std;
typedef map<int, double> Row;
typedef double** Matrix;

typedef struct pgminfo {
  int width;
  int height;
  int max;
  int factor;
  double** pixels;
} PGMInfo;

#endif
