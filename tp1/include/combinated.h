#ifndef __COMBINATED__
#define __COMBINATED__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <tipos.h>
#include <tools.h>

#include <bisection.h>
#include <newton.h>

void combinated_with_friction(Params*);
void combinated_without_friction(Params*);

void combinated(Params*,
    TFloat (*fn_pos)(Params *, TFloat),
    TFloat (*fn_speed)(Params*, TFloat),
    TFloat (*fn_accel)(Params*, TFloat) );

#endif
