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

void combined(Params* p, double (*fn_pos)(Params *, double), double (*fn_speed)(Params*, double), double (*fn_accel)(Params*, double) ) {
  double instant = 0;
  Result res;

  // Primer impacto
  res = zero_bisection(p, fn_pos); // Nos acercamos con bisection
  p->x = res.zero; // Solo actualizamos el punto inicial para Newton
  res = zero_newton(p, fn_pos, fn_speed);

  instant += res.zero;
  printf("  Primer impacto  = %.15lf al instante: %.15lf. Velocidad final = %.15lf \n", fn_pos(p, res.zero), instant, res.speed);

  // Altura Maxima
  p->h = 0;
  p->b = 100 ; // Seteamos el intervalo, luego de hacer consultas no valia la pena calcular cuanto podria ser.
  p->v = -res.speed * p->f;

  res = zero_bisection(p, fn_speed); // Nos acercamos con bisection
  p->x = res.zero;
  res = zero_newton(p, fn_speed, fn_accel);

  printf("  Altura Maxima  = %.15lf al instante: %.15lf. Velocidad final = %.15lf \n", fn_pos(p,res.zero), instant + res.zero, res.speed);

  // Segundo impacto
  res = zero_bisection(p, fn_pos); // Nos acercamos con bisection
  p->x = res.zero;
  res = zero_newton(p, fn_pos, fn_speed);
  instant += res.zero;
  printf("  Segundo impacto = %.15lf al instante: %.15lf. Velocidad final = %.15lf \n", fn_pos(p, res.zero), instant, fn_speed(p, res.zero));
}
