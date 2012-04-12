#ifndef __BISECTION__
#define __BISECTION__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <tipos.h>
#include <tools.h>

void bisection_with_friction(Params*);
void bisection_without_friction(Params*);

void bisection(Params*,
    TFloat (*fn_pos)  (Params*, TFloat),
    TFloat (*fn_speed)(Params*, TFloat),TFloat (*mechanicalToCall)(Params*, TFloat));

Result zero_bisection(Params*, TFloat (*fn)(Params *, TFloat));

#endif
