#ifndef __NEWTON__
#define __NEWTON__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <tipos.h>
#include <tools.h>

void newton(Params*);
void newton_with_friction(Params*);

void zero_position_newton(Params*, double (*functionPositionToCall)(Params *, double), double (*functionSpeedToCall) (Params *, double));
void zero_speed_newton(Params*, double (*functionPositionToCall)(Params *, double), double (*functionSpeedToCall) (Params *, double));


#endif
