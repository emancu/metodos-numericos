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
  printf("  Primer impacto  = %.20lf al instante: %.20lf. Velocidad final = %.20lf \n", fn_pos(p, res.zero), instant, res.speed);
  if(res.iterations == p->max_iterations){
    printf("  SALIO POR ITERACIONES MAXIMAS!!! = %lu \n", p->max_iterations);
  } else{
    printf("  CANT ITERACIONES = %lu , max = %lu\n", res.iterations, p->max_iterations);
    printf("  tolerance %.30lf\n", p->tol_bisect);

  }



/*
  // Altura Maxima
  p->h = 0;
  p->b = 100 ; // FIXME: ver este tema del intervalo que es bastante sensible!!!!!!!!!
  p->v = -res.speed;
  instant += res.zero;
  res = zero_bisection(p, fn_speed);
  printf("  Altura Maxima   = %lf al instante: %lf. Velocidad final = %lf \n", fn_pos(p,res.zero), instant, fn_speed(p,res.zero));

  // Segundo impacto
  zero_bisection(p, fn_pos);
  instant += res.zero;
  printf("  Segundo impacto = %lf al instante: %lf. Velocidad final = %lf \n", fn_pos(p, res.zero), instant, fn_speed(p, res.zero));
  */
}


Result zero_bisection(Params *p, double (*fn)(Params *, double)) {
  unsigned long iteracion = p->max_iterations;
  double a = p->a, b = p->b,m;
  Result res;

  assert_intervals(fn, p);

  while( --iteracion > 0 && !stopping_criteria(a,b, p->tol_bisect)) {
    m = (b+a)/2;
    ( fn(p,a) * fn(p,m) > 0 )? a = m : b = m;
  }

  res.zero = m;
  res.iterations = p->max_iterations - iteracion;

  return res;
}
