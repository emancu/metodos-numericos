#include <tools.h>

double speed(Params *p, double time){
  return p->v - GRAVITY*time;
}

bool stopping_criteria(double a, double b, double tolerance){
  return fabs(a - b) < tolerance;
}

double position(Params *p, double time){
  double h = p->h;
  double v = p->v;
  return h + v*time - GRAVITY*time*time/2;
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

