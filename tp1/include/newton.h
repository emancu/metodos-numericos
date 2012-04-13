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
            TFloat (*fn_pos)   (Params *, TFloat),
            TFloat (*fn_speed) (Params *, TFloat),
            TFloat (*fn_accel) (Params *, TFloat));

Result zero_newton(Params*,
    TFloat (*fn)    (Params *, TFloat),
    TFloat (*deriv) (Params *, TFloat));

#endif
