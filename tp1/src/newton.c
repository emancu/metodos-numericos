#include <newton.h>

void newton_without_friction(Params* p){
  newton(p, &position, &speed, &acceleration);
}

void newton_with_friction(Params* p){
  newton(p, &position_with_friction, &speed_with_friction, &acceleration_with_friction);
}

/*
 * Auxiliar
 */

void newton(Params *p, TFloat (*fn_pos)(Params*, TFloat), TFloat (*fn_speed)(Params*, TFloat), TFloat (*fn_accel)(Params*, TFloat)){
  TFloat instant = 0;
  Result res;

  // Primer impacto
  res = zero_newton(p, fn_pos, fn_speed);
  instant = res.zero;
  output(0, fn_pos(p, res.zero), instant, res.speed);

  // Altura Maxima
  p->h=0;
  p->v = res.speed * -1 * p->f;

  res = zero_newton(p, fn_speed, fn_accel);
  output(1, fn_pos(p,res.zero), instant + res.zero, res.speed);

  // Segundo impacto
  res = zero_newton(p, fn_pos, fn_speed);
  instant = instant + res.zero;
  output(2, fn_pos(p, res.zero), instant, fn_speed(p, res.zero));
}

Result zero_newton(Params* p, TFloat (*fn)(Params *, TFloat), TFloat (*deriv) (Params *, TFloat)){
  TFloat current = p->x, previous = 0.0;
  Result res;
  int i;

  for(i = p->max_iterations; i > 0 && !stopping_criteria(previous, current, p->tol_newton); i--){
    previous = current;
    current = previous - (fn(p, previous)/deriv(p, previous));
  }

  res.speed = deriv(p,current);
  res.zero  = current;
  res.iterations = p->max_iterations - i;

  return res;
}

