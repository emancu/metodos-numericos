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
    TFloat (*fn_pos)(Params *, TFloat),
    TFloat (*fn_speed)(Params*, TFloat),
    TFloat (*fn_accel)(Params*, TFloat) );

#endif
