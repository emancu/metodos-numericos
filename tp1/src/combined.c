#include <combined.h>

void combined_without_friction(Params* p){
  combined(p, &position, &speed, &acceleration);
}

void combined_with_friction(Params* p){
  combined(p, &position_with_friction, &speed_with_friction, &acceleration_with_friction);
}

/*
 * Auxiliar
 */

void combined(Params* p, TFloat (*fn_pos)(Params *, TFloat), TFloat (*fn_speed)(Params*, TFloat), TFloat (*fn_accel)(Params*, TFloat) ) {
  TFloat instant = 0;
  Result res;

  // Primer impacto
  res = zero_bisection(p, fn_pos); // Nos acercamos con bisection
  p->x = res.zero; // Solo actualizamos el punto inicial para Newton
  res = zero_newton(p, fn_pos, fn_speed);

  instant = res.zero;
  output(0, fn_pos(p, res.zero), instant, res.speed);

  // Altura Maxima
  p->h = 0;
  p->b = 100 ; // Seteamos el intervalo, luego de hacer consultas no valia la pena calcular cuanto podria ser.
  p->v = res.speed * -1 * p->f;

  res = zero_bisection(p, fn_speed); // Nos acercamos con bisection
  p->x = res.zero;
  res = zero_newton(p, fn_speed, fn_accel);

  output(1, fn_pos(p,res.zero), instant + res.zero, res.speed);

  // Segundo impacto
  res = zero_bisection(p, fn_pos); // Nos acercamos con bisection
  p->x = res.zero;
  res = zero_newton(p, fn_pos, fn_speed);
  instant = instant + res.zero;
  output(2, fn_pos(p, res.zero), instant, fn_speed(p, res.zero));
}
