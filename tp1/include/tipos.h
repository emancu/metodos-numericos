#ifndef __TIPOS__
#define __TIPOS__

typedef struct str_params {
  // General params
  double h;
  double v;
  double mass;
  double cr;
  double f;
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
  double speed; // FIXME: Quizas no se usa
  double zero;
  int iterations;

} Result;

#endif
