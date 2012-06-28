#ifndef __TOOLS__
#define __TOOLS__
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <string>
#include <iostream>
#include <building.h>

#include <matrix.h>

using namespace std;

Matrix* parse_input(char*);

double* eigenvalues(const Matrix&, double, int);
void qr_decomposition(Matrix*, Matrix*);
void natural_frecuencies(double*, int);
bool is_building_safe(double*, int);
void print_array(double* , int );


#endif
