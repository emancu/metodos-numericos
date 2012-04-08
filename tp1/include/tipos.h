#ifndef __TIPOS__
#define __TIPOS__

typedef struct str_params {
  // General params
  double h;
  double v;
  double t;
  double mass;
  double cr;
  int max_iterations;

  // Bisection params
  double a;
  double b;
  double tol_bisect;

  // Newton params
  double x;
  double tol_newton;
} Params;

typedef struct str_result {
  // General params
  double speed;
  double zero;

} Result;

#endif
