#ifndef __TOOLS__
#define __TOOLS__

#include <math.h>
#include <tipos.h>

#define GRAVITY 9.81

double speed(Params*, double);
double position(Params*, double);
bool stopping_criteria(double, double, double);


double position_with_friction(Params*, double);
double speed_with_friction(Params*, double);

#endif
