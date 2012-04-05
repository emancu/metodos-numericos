#include <bisection.h>


void bisection(Params* p) {
  // Primer impacto
  zero_position(p);

  // Altura Maxima
  //zero_speed(p);

  // segundo impacto
   zero_position(p);
}

void zero_position(Params *p) {
  int    iteracion = p->max_iterations;
  double a = p->a;
  double b = p->b;
  double m;

  if (position(p->h, p->v, a)*position(p->h, p->v, b) > 0){
    printf("Los bordes del intervalo no cumplen las condiciones.\n");
    // assert(true);
  }

  while( --iteracion > 0 && !stopping_criteria(a,b, p->tolerance)) {
    m = (b+a)/2;

    if( position(p->h,p->v,a) * position(p->h,p->v,m) > 0 )
      a = m;
    else
      b = m;
  }

  printf("Alcanza la posicion %lf en el instante %lf a velocidad %lf\n", position(p->h,p->v,m), m, speed(p->v,m));

  p->a = m;
  p->b = 3*m * -p->v; // Arreglar el intervalo, tiene que haber una formula
  p->h = 0;
  p->v = -speed(p->v, m);
}

void zero_speed(Params *p) {
  double m;
  double a = p->a;
  double b = p->b;
  int iteracion = p->max_iterations;

  printf("zero speed con velocidad : %lf \n", p->v);

  if (speed(p->v,a) * speed(p->v,b) > 0){
    printf("Los bordes del intervalo no cumplen las condiciones.\n");
    // assert(true);
  }

  while( --iteracion > 0 && !stopping_criteria(a,b, p->tolerance)) {
    m = (b+a)/2;

    if( speed(p->v,a) * speed(p->v,m) > 0 )
      a = m;
    else
      b = m;
  }

  printf("Max position %lf  en el instante: %lf a velocidad %lf \n", position(p->h,p->v,m),m, speed(p->v,m));

}


/*
 * With Friction
 */



void bisection_with_friction(Params* p) {
  double m;
  double alpha = p->cr/p->mass;
  double a = p->a;
  double b = p->b;
  int i = p->max_iterations;

  while( --i > 0 && !stopping_criteria(a,b, p->tolerance)) {
    m = (b+a)/2;

    if( position_with_friction(p->h,p->v,a, alpha) * position_with_friction(p->h,p->v,m,alpha) > 0 )
      a = m;
    else
      b = m;
  }

  printf("El valor encontrado es %lf en la position %lf a velocidad %lf \n", m, position_with_friction(p->h,p->v,m,alpha), speed_with_friction(p->v,m,alpha));
}
