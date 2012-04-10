#include <newton.h>

void newton_without_friction(Params* p){
  newton(p, &position, &speed, &acceleration);
}

void newton_with_friction(Params* p){
  newton(p, &position_with_friction, &speed_with_friction, &acceleration_with_friction);
}

void newton(Params* p, double (*fn_pos)(Params*, double), double (*fn_speed)(Params*, double), double (*fn_accel)(Params*, double)){
  Result res;
  // Primer impacto
  res = zero_newton(p, fn_pos, fn_speed);
  printf("f= %lf en el instante %lf y f'= %lf \n\n", fn_pos(p, res.zero), res.zero, fn_speed(p,res.zero));
  if(res.iterations == p->max_iterations){
    printf("  SALIO POR ITERACIONES MAXIMAS!!! = %lu \n", p->max_iterations);
  } else{
  printf("  CANT ITERACIONES = %lu \n", res.iterations);
  }
  // Altura Maxima
  // zero_newton(p, &fn_speed, &fn_accel);

  // segundo impacto
  // zero_newton(p, &fn_pos, &fn_speed);
}

/*
 * Auxiliar
 */

Result zero_newton(Params* p, double (*fn)(Params *, double), double (*deriv) (Params *, double)){
  double current = p->x, previous = 0.0;
  Result res;

  printf("Newton con x= %lf \n", current);
  unsigned long i;

  for(i = p->max_iterations; i > 0 && !stopping_criteria(previous, current, p->tol_newton); i--){
    previous = current;
    current = previous - (fn(p, previous)/deriv(p, previous));
  }

  res.speed = deriv(p,current);
  res.zero  = current;
  res.iterations = p->max_iterations - i;

  return res;
}

