#include <combinated.h>

void combinated(Params* p){
  p->t = 0;
  // Primer impacto
  // Cambiar tolerancias y formas de exit

  double backup_tolerance = p->tolerance;

  zero_position_bisection(p, &position, &speed); // Nos acercamos con bisection
  p->tolerance = p->tolerance_combination;

  zero_newton(p, &position, &speed);
  p->tolerance = backup_tolerance;
  // Altura Maxima
  // FIXME: como son
  // zero_speed_bisection(p, &position, &speed); // Nos acercamos con bisection
  // zero_newton(p, &speed, &acceleration);

  // segundo impacto
  // zero_position_bisection(p, &position, &speed); // Nos acercamos con bisection
  // zero_newton(p, &position, &speed);
  // zero_newton(p, &position, &speed);

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
