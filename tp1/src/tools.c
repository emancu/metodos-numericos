#include <tools.h>

/*
 * General
 */

bool stopping_criteria(double a, double b, double tolerance){
  return fabs(a - b) < tolerance;
}

/*
 * Without friction
 */

double speed(Params *p, double time){
  return p->v - GRAVITY*time;
}

double position(Params *p, double time){
  double h = p->h;
  double v = p->v;
  return h + v*time - GRAVITY*time*time/2;
}

// Derivada de ecuacion (2) - Aceleracion
double acceleration(Params *p, double time) {
  return -GRAVITY;
}

double mechanical(Params *p, double time) {
  double d = speed(p, time);
  return GRAVITY * position(p,time) + d*d/2.0;
}


/*
 * With friction
 */

double position_with_friction(Params *p, double time) {
  double h = p->h;
  double v = p->v;
  double alpha = p->cr/p->mass;
  double e = pow(M_E, - alpha * time);
  return h + v/alpha + GRAVITY/(alpha*alpha) - GRAVITY*time/alpha - (v/alpha + GRAVITY/(alpha*alpha)) * e;
}

double speed_with_friction(Params *p, double time) {
  double alpha = p->cr/p->mass;
  double v = p->v;
  double e = pow(M_E, - alpha * time);
  return -GRAVITY/alpha + ( v + GRAVITY/alpha) * e;
}

// Derivada de ecuacion (4) - Aceleracion
double acceleration_with_friction(Params *p, double time) {
  double alpha = p->cr/p->mass;
  double v = alpha * p->v;
  double e = pow(M_E, - alpha * time);

  return (v - GRAVITY) * e;
}

double mechanical_with_friction(Params *p, double time) {
  double d = speed_with_friction(p, time);
  // printf("@@@ d = %lf pos: %lf d*d/2.0:%lf          ++++> time : %lf \n", d, position_with_friction(p, time), d*d/2.0, time);
  return GRAVITY * position_with_friction(p,time) + d*d/2.0;
}

/*
 * Asserts
 */

void assert_intervals(double (*fn)(Params *, double), Params *p) {
  double a = p->a, b = p->b;
  if (fn(p,a) * fn(p,b) > 0){
    printf("-----Los bordes del intervalo no cumplen las condiciones.-----\n");
    printf("Valor a (%lf) => f(a) = %lf ; valor b (%lf) => f(b) = %lf \n\n", a, fn(p, a), b, fn(p, b) );
    exit(1);
  }
}
