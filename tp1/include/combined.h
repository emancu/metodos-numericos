#ifndef __COMBINED__
#define __COMBINED__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <tipos.h>
#include <tools.h>

#include <bisection.h>
#include <newton.h>

void combined_with_friction(Params*);
void combined_without_friction(Params*);

void combined(Params*,
    double (*fn_pos)(Params *, double),
    double (*fn_speed)(Params*, double),
    double (*fn_accel)(Params*, double) );

#endif
