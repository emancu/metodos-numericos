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
    double (*fn_pos)(Params *, double),
    double (*fn_speed)(Params*, double),
    double (*fn_accel)(Params*, double) );

#endif
