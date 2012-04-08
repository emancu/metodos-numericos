#ifndef __BISECTION__
#define __BISECTION__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <tipos.h>
#include <tools.h>

void bisection(Params*);
void bisection_with_friction(Params*);

void zero_position_bisection(Params*, double (*functionPositionToCall)(Params *, double), double (*functionSpeedToCall) (Params *, double));
void zero_speed_bisection(Params*, double (*functionPositionToCall)(Params *, double), double (*functionSpeedToCall) (Params *, double));

#endif
