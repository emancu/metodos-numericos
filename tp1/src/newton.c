#include <newton.h>

void newton_without_friction(Params* p){
  newton(p, &position, &speed, &acceleration);
}

void newton_with_friction(Params* p){
  newton(p, &position_with_friction, &speed_with_friction, &acceleration_with_friction);
}

void newton(Params* p, TFloat (*fn_pos)(Params*, TFloat), TFloat (*fn_speed)(Params*, TFloat), TFloat (*fn_accel)(Params*, TFloat)){
  Result res;
  TFloat instant = TFloat(0,T);
  // Primer impacto
  res = zero_newton(p, fn_pos, fn_speed);
  instant = instant + res.zero;
  printf("  Primer impacto  = %.15lf al instante: %.15lf. Velocidad final = %.15lf \n", fn_pos(p, res.zero).dbl(), instant.dbl(), res.speed.dbl());
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

Result zero_newton(Params* p, TFloat (*fn)(Params *, TFloat), TFloat (*deriv) (Params *, TFloat)){
  TFloat current = p->x, previous = 0.0;
  Result res;

  printf("Newton con x= %.15lf \n", current.dbl());
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

