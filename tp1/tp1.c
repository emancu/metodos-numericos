#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define GRAVITY 9.81

typedef struct params {
  // General params
  double h;
  double v;
  double tolerance;
  double mass;
  double cr;
  int max_iterations;

  // Bisection params
  double a;
  double b;

  // Newton params
  double x;
} params;

void newton(params);
void bisection(params);
double speed(double, double);
double position(double, double, double);
bool stopping_criteria(double, double, double);

void bisection_with_friction(params);
void newton_with_friction(params);
double position_with_friction(double h, double v, double time, double alpha);
double speed_with_friction(double, double, double);


/*
 *  Main
 */

int main(int argc, char* argv[]){
  // Aca se asignan los params parseados del CLI al estilo -h <valor> -v <valor>
  static const char *optString = "M::h::v::t::m::c::i::a::b::x::";
  int method;
  params p;
  int c;
  while((c = getopt(argc, argv, optString)) != -1){
    switch(c){
      case 'M':
        method = atoi(optarg);
        break;
      case 'h':
        p.h = atof(optarg);
        break;
      case 'v':
        p.v = atof(optarg);
        break;
      case 't':
        p.tolerance = atof(optarg);
        break;
      case 'm':
        p.mass = atof(optarg);
        break;
      case 'c':
        p.cr = atof(optarg);
        break;
      case 'i':
        p.max_iterations = atoi(optarg);
        break;
      case 'a':
        p.a = atof(optarg);
        break;
      case 'b':
        p.b = atof(optarg);
        break;
      case 'x':
        p.x = atof(optarg);
        break;
      default:
        printf("no te parseo un carajo\n");
        break;
    }
  }

  switch(method) {
    case 0:
      printf("Bisection: \n");
      bisection(p);
      break;
    case 1:
      printf("Bisection with friction: \n");
      bisection_with_friction(p);
      break;
    case 2:
      printf("Newton: \n");
      newton(p);
      break;
    case 3:
      printf("Newton with friction: \n");
      newton_with_friction(p);
      break;
    default:
      printf("Metodo no valido.\n");
  }

  return 0;
}


/*
 * Methods
 */

void bisection(params p) {
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

void newton(params p){
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

void newton_with_friction(params p){
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

void bisection_with_friction(params p) {
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
  return -GRAVITY/alpha + ( v + GRAVITY/alpha) * e;
}

