#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define GRAVITY 9.81

void newton(char**);
void bisection(char**);
double speed(double, double);
bool termino(double, double);
double position(double, double, double);
int stopping_criteria(double, double, double);


/*
 *  Main
 */


int main(int r, char* argv[]){

  int method = atoi(argv[1]);

  switch(method) {
    case 0:
      bisection(argv);
      break;
    case 1:
      newton(argv);
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
  int iteracion = atoi(argv[6]);

  if (position(h, vi, a)*position(h, vi, b) > 0){
    printf("Los bordes del intervalo no cumplen las condiciones.\n");
    // assert(true);
  }


  while( --iteracion > 0 && !termino(a,b)) {
    m = (b+a)/2;

    if( position(h,vi,a) * position(h,vi,m) > 0 )
      a = m;
    else
      b = m;
  }

  printf("El valor encontrado es %lf en la position %lf \n", m, position(h,vi,m));
}


void newton(char* argv[]){
  double h, v, previous, current, tolerance;
  int max_iterations, i;
  h = atof(argv[1]);
  v = atof(argv[2]);
  current = atof(argv[3]);
  max_iterations = atoi(argv[4]);
  tolerance = atof(argv[5]);

  previous = 0.0;
  for(i = 0; i < max_iterations && !stopping_criteria(previous, current, tolerance); i++){
    previous = current;
    current = previous - (position(h, v, previous)/speed(v, previous));
  }

  printf("%f\n", current);
}

int stopping_criteria(double previous, double current, double tolerance){
  return fabs(current - previous) < tolerance;
}


bool termino(double a, double b) {
  return fabs(a-b) < 0.00000000000001;
}

double position(double h, double v, double time){
  return h + v*time - GRAVITY*time*time/2;
}

double speed(double v, double time){
  return v - GRAVITY*time;
}
