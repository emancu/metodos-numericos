#include <bisection.h>


void bisection(Params* p) {
  p->t = 0;
  // Primer impacto
  zero_position_biseccion(p, &position, &speed);

  // Altura Maxima
  zero_speed_biseccion(p, &position, &speed);

  // segundo impacto
  zero_position_biseccion(p, &position, &speed);
}


void bisection_with_friction(Params* p) {
  p->t = 0;
  zero_position_biseccion(p, &position_with_friction, &speed_with_friction);

  //Altura Maxima
  zero_speed_biseccion(p, &position_with_friction, &speed_with_friction);

  // segundo impacto
  zero_position_biseccion(p, &position_with_friction, &speed_with_friction);
}


void zero_position_biseccion(Params *p, double (*functionPositionToCall)(Params *, double), double (*functionSpeedToCall) (Params *, double)) {
  int    iteracion = p->max_iterations;
  double a = p->a;
  double b = p->b;
  double m;

  printf("tolerance = %.10f\n" , p->tolerance);


  if ( functionPositionToCall(p,a)*functionPositionToCall(p,b) > 0){
    printf("-----Los bordes del intervalo no cumplen las condiciones.-----\n");
    // assert(true);
  }

  while( --iteracion > 0 && !stopping_criteria(a,b, p->tolerance)) {
    m = (b+a)/2;

    if( functionPositionToCall(p,a) * functionPositionToCall(p,m) > 0 )
      a = m;
    else
      b = m;
  }

  p->t = p->t + m;
  printf("Alcanza la posicion %lf en el instante %lf a velocidad %lf\n\n", functionPositionToCall(p,m), p->t, functionSpeedToCall(p,m));

  //p->a = m;
  p->b = 100 ; // todo ver este tema del intervalo que es bastante sensible!!!!!!!!!
  p->h = 0;
  p->v = -functionSpeedToCall(p, m);
}

void zero_speed_biseccion(Params *p, double (*functionPositionToCall)(Params *, double), double (*functionSpeedToCall) (Params *, double)) {
  double m;
  double a = p->a;
  double b = p->b;
  int iteracion = p->max_iterations;

  printf("zero speed con velocidad : %lf \n", p->v);

  if (functionSpeedToCall(p,a) * functionSpeedToCall(p,b) > 0){
    printf("-----Los bordes del intervalo no cumplen las condiciones.-----\n");
    printf("Valor a (%lf) => f(a) = %lf ; valor b (%lf) => f(b) = %lf \n\n" ,a,functionSpeedToCall(p,a),b,functionSpeedToCall(p,b) );
    // assert(true);
  }

  while( --iteracion > 0 && !stopping_criteria(a,b, p->tolerance)) {
    m = (b+a)/2;

    if( functionSpeedToCall(p,a) * functionSpeedToCall(p,m) > 0 )
      a = m;
    else
      b = m;
  }

  printf("Max position %lf  en el instante: %lf a velocidad %lf \n\n", functionPositionToCall(p,m),p->t + m, functionSpeedToCall(p,m));
}
