#include <combined.h>


void combined_without_friction(Params* p){
  newton(p, &position, &speed, &acceleration);
}

void combined_with_friction(Params* p){
  newton(p, &position_with_friction, &speed_with_friction, &acceleration_with_friction);
}

/*
 * Auxiliar
 */

void combined(Params* p, double (*fn_pos)(Params *, double), double (*fn_speed)(Params*, double), double (*fn_accel)(Params*, double) ) {
  Result res;

  // Primer impacto
  res = zero_bisection(p, fn_pos); // Nos acercamos con bisection

  // Solo actualizamos el punto inicial para Newton
  p->x = res.zero;

  res = zero_newton(p, fn_pos, fn_speed);

  // Altura Maxima

  p->h = 0;
  p->b = 100 ; // FIXME: ver este tema del intervalo que es bastante sensible!!!!!!!!!
  p->v = -res.speed;
  res = zero_bisection(p, fn_speed); // Nos acercamos con bisection

  p->x = res.zero;

  res = zero_newton(p, fn_speed, fn_accel);
  printf("Altura %lf \n", fn_pos(p, res.zero));

  // Segundo impacto

  res = zero_bisection(p, fn_pos); // Nos acercamos con bisection
  p->x = res.zero;
  zero_newton(p, fn_pos, fn_speed);

}
