#ifndef __NEWTON__
#define __NEWTON__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <tipos.h>
#include <tools.h>

void newton_with_friction(Params*);
void newton_without_friction(Params*);

void newton(Params*,
            double (*fn_pos)   (Params *, double),
            double (*fn_speed) (Params *, double),
            double (*fn_accel) (Params *, double));

Result zero_newton(Params*,
    double (*fn)    (Params *, double),
    double (*deriv) (Params *, double));

#endif
