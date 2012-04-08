#ifndef __BISECTION__
#define __BISECTION__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <tipos.h>
#include <tools.h>

void bisection_with_friction(Params*);
void bisection_without_friction(Params*);

void bisection(Params*, double (*fn_pos)(Params*, double), double (*fn_speed)(Params*, double));
Result zero_bisection(Params*, double (*fn)(Params *, double));

#endif
