#ifndef __BISECTION__
#define __BISECTION__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <tipos.h>
#include <tools.h>

void bisection(Params*);
void bisection_with_friction(Params*);

void zero_position(Params*);
void zero_speed(Params*);

#endif
