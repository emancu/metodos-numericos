#ifndef __TIPOS__
#define __TIPOS__

typedef struct str_params {
  // General params
  double h;
  double v;
  double t;
  double tolerance;
  double mass;
  double cr;
  int max_iterations;

  double tolerance_combination;

  // Bisection params
  double a;
  double b;

  // Newton params
  double x;
} Params;


#endif
