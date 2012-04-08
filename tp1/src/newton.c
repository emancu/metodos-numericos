#include <newton.h>

void newton(Params* p){
  p->t = 0;
  // Primer impacto
  zero_newton(p, &position, &speed);

  // Altura Maxima
  // zero_newton(p, &speed, &acceleration);

  // segundo impacto
  // zero_newton(p, &position, &speed);

}


void newton_with_friction(Params* p){
  p->t = 0;
  // Primer impacto
  zero_newton(p, &position_with_friction, &speed_with_friction);

  // Altura Maxima
  // zero_newton(p, &speed_with_friction, &acceleration_with_friction);

  // segundo impacto
  // zero_newton(p, &position_with_friction, &speed_with_friction);
}

Result zero_newton(Params* p, double (*fn)(Params *, double), double (*deriv) (Params *, double)){
  Result res;
  int i;
  double current = p->x;
  double previous = 0.0;

  printf("Newton con x= %lf \n", current);

  for(i = 0; i < p->max_iterations && !stopping_criteria(previous, current, p->tol_newton); i++){
    previous = current;
    current = previous - (fn(p, previous)/deriv(p, previous));
  }

  printf("f= %lf en el instante %lf y f'= %lf \n\n", fn(p,current), current, deriv(p,current));

  res.speed = deriv(p,current);
  res.zero  = current;

  return res;
}

