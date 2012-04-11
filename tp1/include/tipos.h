#ifndef __TIPOS__
#define __TIPOS__

#include <TFloat.h>

typedef struct str_params {
  // General params
  TFloat h;
  TFloat v;
  TFloat mass;
  TFloat cr;
  unsigned long  max_iterations;

  // Bisection params
  TFloat a;
  TFloat b;
  TFloat tol_bisect;

  // Newton params
  TFloat x;
  TFloat tol_newton;
} Params;

typedef struct str_result {
  // General params
  TFloat speed; // FIXME: Quizas no se usa
  TFloat zero;
  unsigned long iterations;

} Result;

#endif
