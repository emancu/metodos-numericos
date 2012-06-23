#ifndef __TOOLS__
#define __TOOLS__
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <string>
#include <iostream>

#include <matrix.h>

using namespace std;

Matrix* parse_input(char*);

void carvalues(const Matrix&);
void qr_decomposition(Matrix*, Matrix*);


#endif
