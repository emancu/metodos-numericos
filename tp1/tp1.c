#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define GRAVITY 9.81

void newton(char**);
void bisection(char**);
double speed(double, double);
double position(double, double, double);
bool stopping_criteria(double, double, double);

void bisection_with_friction(char**);
void newton_with_friction(char**);
double position_with_friction(double h, double v, double time, double alpha);
double speed_with_friction(double, double, double);


/*
 *  Main
 */


int main(int r, char* argv[]){

  int method = atoi(argv[1]);

  switch(method) {
    case 0:
      printf("Bisection: \n");
      bisection(argv);
      break;
    case 1:
      printf("Bisection with friction: \n");
      bisection_with_friction(argv);
      break;
    case 2:
      printf("Newton: \n");
      newton(argv);
      break;
    case 3:
      printf("Newton with friction: \n");
      newton_with_friction(argv);
      break;
    default:
      printf("Metodo no valido.\n");
  }

  return 0;
}


/*
 * Methods
 */


void bisection(char* argv[]) {
  double m;

  double h  = atof(argv[2]);
  double vi = atof(argv[3]);
  double a  = atof(argv[4]);
  double b  = atof(argv[5]);
  double tolerance  = atof(argv[6]);
  int iteracion = atoi(argv[7]);

  if (position(h, vi, a)*position(h, vi, b) > 0){
    printf("Los bordes del intervalo no cumplen las condiciones.\n");
    // assert(true);
  }


  while( --iteracion > 0 && !stopping_criteria(a,b, tolerance)) {
    m = (b+a)/2;

    if( position(h,vi,a) * position(h,vi,m) > 0 )
      a = m;
    else
      b = m;
  }

  printf("El valor encontrado es %lf en la position %lf a velocidad %lf \n", m, position(h,vi,m), speed(vi,m));
}


void newton(char* argv[]){
  double h, v, previous, current, tolerance;
  int max_iterations, i;
  h = atof(argv[2]);
  v = atof(argv[3]);
  current = atof(argv[4]);
  max_iterations = atoi(argv[5]);
  tolerance = atof(argv[6]);

  previous = 0.0;
  for(i = 0; i < max_iterations && !stopping_criteria(previous, current, tolerance); i++){
    previous = current;
    current = previous - (position(h, v, previous)/speed(v, previous));
  }

  // printf("%f\n", current);
  double m = current;
  printf("El valor encontrado es %lf en la position %lf a velocidad %lf \n", m, position(h,v,m), speed(v,m));
}

void newton_with_friction(char* argv[]){
  double h, v, previous, current, tolerance, mass, cr;
  int max_iterations, i;
  h = atof(argv[2]);
  v = atof(argv[3]);
  current = atof(argv[4]);
  max_iterations = atoi(argv[5]);
  tolerance = atof(argv[6]);
  mass = atof(argv[7]);
  cr = atof(argv[8]);

  double alpha = cr/mass;

  previous = 0.0;
  for(i = 0; i < max_iterations && !stopping_criteria(previous, current, tolerance); i++){
    previous = current;
    current = previous - (position_with_friction(h, v, previous, alpha)/speed_with_friction(v, previous, alpha));
  }

  // printf("%f\n", current);
  double m = current;
  printf("El valor encontrado es %lf en la position %lf a velocidad %lf \n", m, position_with_friction(h,v,m, alpha), speed_with_friction(v,m, alpha));
}

void bisection_with_friction(char* argv[]) {
  double m;

  double h  = atof(argv[2]);
  double vi = atof(argv[3]);
  double a  = atof(argv[4]);
  double b  = atof(argv[5]);
  double tolerance  = atof(argv[6]);
  int iteracion = atoi(argv[7]);

  double mass = atof(argv[8]);
  double cr = atof(argv[9]);
  double alpha = cr/mass;

  while( --iteracion > 0 && !stopping_criteria(a,b, tolerance)) {
    m = (b+a)/2;

    if( position_with_friction(h,vi,a, alpha) * position_with_friction(h,vi,m,alpha) > 0 )
      a = m;
    else
      b = m;
  }

  printf("El valor encontrado es %lf en la position %lf a velocidad %lf \n", m, position_with_friction(h,vi,m,alpha), speed_with_friction(vi,m,alpha));
}

/*
 * Auxiliar
 */

bool stopping_criteria(double a, double b, double tolerance){
  return fabs(a - b) < tolerance;
}

double position(double h, double v, double time){
  return h + v*time - GRAVITY*time*time/2;
}

double speed(double v, double time){
  return v - GRAVITY*time;
}

double position_with_friction(double h, double v, double time, double alpha) {
  double e = pow(M_E, - alpha * time);
  return h + v/alpha + GRAVITY/(alpha*alpha) - GRAVITY*time/alpha - (v/alpha + GRAVITY/(alpha*alpha)) * e;
}

double speed_with_friction(double v, double time, double alpha) {
  double e = pow(M_E, - alpha * time);
  return -GRAVITY/alpha -( v + GRAVITY/alpha) * e;
}

