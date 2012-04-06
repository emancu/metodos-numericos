#include <newton.h>

void newton(Params* p){
  p->t = 0;
  // Primer impacto
  zero_position_newton(p, &position, &speed);

  // Altura Maxima
  //zero_speed_newton(p, &position, &speed);

  // segundo impacto
  //zero_position_newton(p, &position, &speed);

}


void newton_with_friction(Params* p){
  p->t = 0;
  // Primer impacto
  zero_position_newton(p, &position_with_friction, &speed_with_friction);

  // Altura Maxima
  //zero_speed_newton(p, &position_with_friction, &speed_with_friction);

  // segundo impacto
  //zero_position_newton(p, &position_with_friction, &speed_with_friction);
}

void zero_position_newton(Params* p, double (*functionPositionToCall)(Params *, double), double (*functionSpeedToCall) (Params *, double)){
  int i;
  double current = p->x;
  double previous = 0.0;
  for(i = 0; i < p->max_iterations && !stopping_criteria(previous, current, p->tolerance); i++){
    previous = current;
    current = previous - (functionPositionToCall(p, previous)/functionSpeedToCall(p, previous));
  }

  double m = current;
  printf("Alcanza la posicion %lf en el instante %lf a velocidad %lf\n\n", functionPositionToCall(p,m), m, functionSpeedToCall(p,m));
}

void zero_speed_newton(Params* p, double (*functionPositionToCall)(Params *, double), double (*functionSpeedToCall) (Params *, double)){
  //FALTA IMPLEMENTAR
}







