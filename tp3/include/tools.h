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
void print_array(double* , int);

bool stop_criteria_only_sub_diagonal(int, double*,double*, double);


#endif
