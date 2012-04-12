#include <bisection.h>

void bisection_without_friction(Params* p) {
  bisection(p, &position, &speed);
}

void bisection_with_friction(Params* p) {
  bisection(p, &position_with_friction, &speed_with_friction);
}

/*
 * Auxiliar
 */

void bisection(Params* p, double (*fn_pos)(Params*,double), double (*fn_speed)(Params*, double)) {
  double instant = 0;
  Result res;

  // Primer impacto
  res = zero_bisection(p, fn_pos);
  res.speed = fn_speed(p,res.zero);
  instant += res.zero;
  printf("  Primer impacto  = %.15lf al instante: %.15lf. Velocidad final = %.15lf \n", fn_pos(p, res.zero), instant, res.speed);

  // Altura Maxima
  p->h = 0;
  p->b = 100 ; // Seteamos el intervalo, luego de hacer consultas no valia la pena calcular cuanto podria ser.
  p->v = -res.speed * p->f;

  res = zero_bisection(p, fn_speed);
  printf("  Altura Maxima   = %.15lf al instante: %.15lf. Velocidad final = %.15lf \n", fn_pos(p,res.zero), instant + res.zero, fn_speed(p,res.zero));

  // Segundo impacto
  res = zero_bisection(p, fn_pos);
  instant += res.zero;
  printf("  Segundo impacto = %.15lf al instante: %.15lf. Velocidad final = %.15lf \n", fn_pos(p, res.zero), instant, fn_speed(p, res.zero));
}


Result zero_bisection(Params *p, double (*fn)(Params *, double)) {
  int    iteracion = p->max_iterations;
  double a = p->a, b = p->b;
  Result res;

  assert_intervals(fn, p);

  while( --iteracion > 0 && !stopping_criteria(a,b, p->tol_bisect)) {
    res.zero = (b+a)/2;
    ( fn(p,a) * fn(p, res.zero) > 0 )? a = res.zero : b = res.zero;
  }

  res.iterations = p->max_iterations - iteracion;

  return res;
}
