#ifndef __TOOLS__
#define __TOOLS__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <tipos.h>

#define GRAVITY TFloat(9.81, T)
#define T 52

bool stopping_criteria(TFloat, TFloat, TFloat);
void output(int, TFloat, TFloat, TFloat);
void mechanical_energy_output(TFloat, TFloat, TFloat);

TFloat speed(Params*, TFloat);
TFloat position(Params*, TFloat);
TFloat acceleration(Params *, TFloat);
TFloat mechanical(Params *, TFloat);

TFloat position_with_friction(Params*, TFloat);
TFloat speed_with_friction(Params*, TFloat);
TFloat acceleration_with_friction(Params *, TFloat);
TFloat mechanical_with_friction(Params *, TFloat);

/*
 * Asserts
 */

void assert_intervals(TFloat (*fn)(Params *, TFloat), Params *p);


#endif
