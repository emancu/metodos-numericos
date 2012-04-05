#include <tools.h>

double speed(double v, double time){
  return v - GRAVITY*time;
}

bool stopping_criteria(double a, double b, double tolerance){
  return fabs(a - b) < tolerance;
}

double position(double h, double v, double time){
  return h + v*time - GRAVITY*time*time/2;
}

/*
 * With friction
 */

double position_with_friction(double h, double v, double time, double alpha) {
  double e = pow(M_E, - alpha * time);
  return h + v/alpha + GRAVITY/(alpha*alpha) - GRAVITY*time/alpha - (v/alpha + GRAVITY/(alpha*alpha)) * e;
}

double speed_with_friction(double v, double time, double alpha) {
  double e = pow(M_E, - alpha * time);
  return -GRAVITY/alpha + ( v + GRAVITY/alpha) * e;
}

