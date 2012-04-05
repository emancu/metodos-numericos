#ifndef __TOOLS__
#define __TOOLS__

#include <math.h>

#define GRAVITY 9.81

double speed(double, double);
double position(double, double, double);
bool stopping_criteria(double, double, double);

double position_with_friction(double h, double v, double time, double alpha);
double speed_with_friction(double, double, double);

#endif
