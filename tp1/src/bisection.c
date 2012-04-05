#include <bisection.h>

void bisection(Params p) {
  double m;
  double a = p.a;
  double b = p.b;
  int iteracion = p.max_iterations;

  if (position(p.h, p.v, a)*position(p.h, p.v, b) > 0){
    printf("Los bordes del intervalo no cumplen las condiciones.\n");
    // assert(true);
  }


  while( --iteracion > 0 && !stopping_criteria(a,b, p.tolerance)) {
    m = (b+a)/2;

    if( position(p.h,p.v,a) * position(p.h,p.v,m) > 0 )
      a = m;
    else
      b = m;
  }

  printf("El valor encontrado es %lf en la position %lf a velocidad %lf \n", m, position(p.h,p.v,m), speed(p.v,m));

}


void bisection_with_friction(Params p) {
  double m;
  double alpha = p.cr/p.mass;
  double a = p.a;
  double b = p.b;
  int i = p.max_iterations;

  while( --i > 0 && !stopping_criteria(a,b, p.tolerance)) {
    m = (b+a)/2;

    if( position_with_friction(p.h,p.v,a, alpha) * position_with_friction(p.h,p.v,m,alpha) > 0 )
      a = m;
    else
      b = m;
  }

  printf("El valor encontrado es %lf en la position %lf a velocidad %lf \n", m, position_with_friction(p.h,p.v,m,alpha), speed_with_friction(p.v,m,alpha));
}
