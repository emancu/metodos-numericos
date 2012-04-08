#include <combinated.h>

void combinated(Params* p){
  Result res;
  p->t = 0;

  // Primer impacto
  res = zero_position_bisection(p, &position, &speed); // Nos acercamos con bisection

  // Solo actualizamos el punto inicial para Newton
  p->x = res.zero;

  res = zero_newton(p, &position, &speed);

  // Altura Maxima

  p->h = 0;
  p->b = 100 ; // FIXME: ver este tema del intervalo que es bastante sensible!!!!!!!!!
  p->v = -res.speed;
  res = zero_speed_bisection(p, &position, &speed); // Nos acercamos con bisection

  p->x = res.zero;

  res = zero_newton(p, &speed, &acceleration);
  printf("Altura %lf \n", position(p, res.zero));


  // Segundo impacto

  res = zero_position_bisection(p, &position, &speed); // Nos acercamos con bisection
  p->x = res.zero;
  zero_newton(p, &position, &speed);

}


void combinated_with_friction(Params* p){
  p->t = 0;
  // Primer impacto
  zero_newton(p, &position_with_friction, &speed_with_friction);

  // Altura Maxima
  // zero_newton(p, &speed_with_friction, &acceleration_with_friction);

  // segundo impacto
  // zero_newton(p, &position_with_friction, &speed_with_friction);
}
