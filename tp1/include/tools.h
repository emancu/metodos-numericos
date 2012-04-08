#ifndef __TOOLS__
#define __TOOLS__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <tipos.h>

#define GRAVITY 9.81

bool stopping_criteria(double, double, double);

double speed(Params*, double);
double position(Params*, double);
double acceleration(Params *p, double time);

double position_with_friction(Params*, double);
double speed_with_friction(Params*, double);
double acceleration_with_friction(Params *p, double time);

/*
 * Asserts
 */

void assert_intervals(double (*fn)(Params *, double), Params *p);


#endif
