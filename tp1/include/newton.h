#ifndef __NEWTON__
#define __NEWTON__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <tipos.h>
#include <tools.h>

void newton(Params*);
void newton_with_friction(Params*);

Result zero_newton(Params*, double (*fn)(Params *, double), double (*deriv) (Params *, double));

#endif
