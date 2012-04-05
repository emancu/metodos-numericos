#include <newton.h>

void newton(Params p){
  int i;
  double current = p.x;
  double previous = 0.0;
  for(i = 0; i < p.max_iterations && !stopping_criteria(previous, current, p.tolerance); i++){
    previous = current;
    current = previous - (position(p.h, p.v, previous)/speed(p.v, previous));
  }

  double m = current;
  printf("El valor encontrado es %lf en la position %lf a velocidad %lf \n", m, position(p.h,p.v,m), speed(p.v,m));
}


void newton_with_friction(Params p){
  int i;
  double alpha    = p.cr/p.mass;
  double current  = p.x;
  double previous = 0.0;
  for(i = 0; i < p.max_iterations && !stopping_criteria(previous, current, p.tolerance); i++){
    previous = current;
    current = previous - (position_with_friction(p.h, p.v, previous, alpha)/speed_with_friction(p.v, previous, alpha));
  }

  double m = current;
  printf("El valor encontrado es %lf en la position %lf a velocidad %lf \n", m, position_with_friction(p.h,p.v,m, alpha), speed_with_friction(p.v,m, alpha));
}


