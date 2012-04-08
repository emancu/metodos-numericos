#include <bisection.h>


void bisection(Params* p) {
  Result res;
  p->t = 0;
  // Primer impacto
  res = zero_position_bisection(p, &position, &speed);

  // Altura Maxima
  p->h = 0;
  p->b = 100 ; // FIXME: ver este tema del intervalo que es bastante sensible!!!!!!!!!
  p->v = -res.speed;
  zero_speed_bisection(p, &position, &speed);

  // segundo impacto
  zero_position_bisection(p, &position, &speed);
}


void bisection_with_friction(Params* p) {
  p->t = 0;
  zero_position_bisection(p, &position_with_friction, &speed_with_friction);

  //Altura Maxima
  zero_speed_bisection(p, &position_with_friction, &speed_with_friction);

  // segundo impacto
  zero_position_bisection(p, &position_with_friction, &speed_with_friction);
}


Result zero_position_bisection(Params *p, double (*functionPositionToCall)(Params *, double), double (*functionSpeedToCall) (Params *, double)) {
  Result res;
  int    iteracion = p->max_iterations;
  double a = p->a;
  double b = p->b;
  double m;

  printf("Tolerance = %.10f\n" , p->tol_bisect);


  if ( functionPositionToCall(p,a)*functionPositionToCall(p,b) > 0){
    printf("-----Los bordes del intervalo no cumplen las condiciones.-----\n");
    // assert(true);
  }

  while( --iteracion > 0 && !stopping_criteria(a,b, p->tol_bisect)) {
    m = (b+a)/2;

    if( functionPositionToCall(p,a) * functionPositionToCall(p,m) > 0 )
      a = m;
    else
      b = m;
  }

  //FIXME: Corregir!
  p->t = p->t + m;
  printf("Alcanza la posicion %lf en el instante %lf a velocidad %lf\n\n", functionPositionToCall(p,m), p->t, functionSpeedToCall(p,m));

  res.speed = functionSpeedToCall(p,m);
  res.zero = m;

  return res;
}

Result zero_speed_bisection(Params *p, double (*functionPositionToCall)(Params *, double), double (*functionSpeedToCall) (Params *, double)) {
  Result res;
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

  while( --iteracion > 0 && !stopping_criteria(a,b, p->tol_bisect)) {
    m = (b+a)/2;

    if( functionSpeedToCall(p,a) * functionSpeedToCall(p,m) > 0 )
      a = m;
    else
      b = m;
  }

  printf("Max position %lf  en el instante: %lf a velocidad %lf \n\n", functionPositionToCall(p,m),p->t + m, functionSpeedToCall(p,m));
  res.speed = functionPositionToCall(p,m);
  res.zero  = m;

  return res;
}
