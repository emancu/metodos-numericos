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
  static const char *optString = "Mhvtmciabx:";
  int method;
  params p;
  int c;
  while(c = getopt(argc, argv, optString) != -1){
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
        printf("no te parseo un carajo");
    }
  }

  // int method            = atoi(argv[1]);
  // p.h              = atof(argv[2]);
  // p.v              = atof(argv[3]);
  // p.tolerance      = atof(argv[4]);
  // p.mass           = atof(argv[5]);
  // p.cr             = atof(argv[6]);
  // p.max_iterations = atoi(argv[7]);
  // p.a              = atof(argv[8]);
  // p.b              = atof(argv[9]);
  // p.x              = atof(argv[10]);

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

  //double h  = atof(argv[2]);
  //double vi = atof(argv[3]);
  //double a  = atof(argv[4]);
  //double b  = atof(argv[5]);
  //double tolerance  = atof(argv[6]);
  int iteracion = p.max_iterations;

  if (position(p.h, p.v, p.a)*position(p.h, p.v, p.b) > 0){
    printf("Los bordes del intervalo no cumplen las condiciones.\n");
    // assert(true);
  }


  while( --iteracion > 0 && !stopping_criteria(p.a,p.b, p.tolerance)) {
    m = (p.b+p.a)/2;

    if( position(p.h,p.v,p.a) * position(p.h,p.v,m) > 0 )
      a = m;
    else
      b = m;
  }

  printf("El valor encontrado es %lf en la position %lf a velocidad %lf \n", m, position(h,vi,m), speed(vi,m));
}


void newton(params p){
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

  double m = current;
  printf("El valor encontrado es %lf en la position %lf a velocidad %lf \n", m, position(h,v,m), speed(v,m));
}

void newton_with_friction(params p){
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

  double m = current;
  printf("El valor encontrado es %lf en la position %lf a velocidad %lf \n", m, position_with_friction(h,v,m, alpha), speed_with_friction(v,m, alpha));
}

void bisection_with_friction(params p) {
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
  return -GRAVITY/alpha + ( v + GRAVITY/alpha) * e;
}

