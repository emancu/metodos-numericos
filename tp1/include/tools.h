#ifndef __TOOLS__
#define __TOOLS__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <tipos.h>


#define T 52
#define GRAVITY TFloat(9.81,T)



bool stopping_criteria(TFloat, TFloat, TFloat);

TFloat speed(Params*, TFloat);
TFloat position(Params*, TFloat);
TFloat acceleration(Params *p, TFloat);

TFloat position_with_friction(Params*, TFloat);
TFloat speed_with_friction(Params*, TFloat);
TFloat acceleration_with_friction(Params *p, TFloat);



TFloat mechanical_without(Params *p, TFloat time);
TFloat mechanical_with_friction(Params *p, TFloat time);



/*
 * Asserts
 */

void assert_intervals(TFloat (*fn)(Params *, TFloat), Params *p);


#endif
