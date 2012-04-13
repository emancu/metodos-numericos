#include <stdio.h>
#include <unistd.h>
#include <tipos.h>
#include <newton.h>
#include <bisection.h>
#include <combined.h>

/*
 *  Main
 */

int main(int argc, char* argv[]){
  // Aca se asignan los params parseados del CLI al estilo -h <valor> -v <valor>
  static const char *optString = "M:h:v:t:m:c:i:a:b:x:z:f:";
  int method, c;
  char * pEnd;
  Params p;

  // Default params
  p.f = 1;
  p.max_iterations = 1000000;
  p.tol_bisect = 0.000000000000001;
  p.tol_newton = 0.000000000000001;


  while((c = getopt(argc, argv, optString)) != -1){
    switch(c){
      case 'M': { method = atoi(optarg);                              break; }
      case 'h': { p.h = TFloat(atof(optarg),T);                       break; }
      case 'v': { p.v = TFloat(atof(optarg),T);                       break; }
      case 't': { p.tol_bisect = TFloat(atof(optarg),T);              break; }
      case 'm': { p.mass = TFloat(atof(optarg),T);                    break; }
      case 'c': { p.cr = TFloat(atof(optarg),T);                      break; }
      case 'i': { p.max_iterations = strtoul(optarg,&pEnd,10);        break; }
      case 'a': { p.a = TFloat(atof(optarg),T);                       break; }
      case 'b': { p.b = TFloat(atof(optarg),T);                       break; }
      case 'x': { p.x = TFloat(atof(optarg),T);                       break; }
      case 'z': { p.tol_newton = TFloat(atof(optarg),T);              break; }
      case 'f': { p.f = TFloat(atof(optarg),T);                       break; }
      default:  { printf("Cannot parse.\n"); }
    }
  }

  switch(method) {
    case 0:  { printf("Bisection: \n");               bisection_without_friction(&p);   break; }
    case 1:  { printf("Bisection with friction:\n");  bisection_with_friction(&p);      break; }
    case 2:  { printf("Newton: \n");                  newton_without_friction(&p);      break; }
    case 3:  { printf("Newton with friction: \n");    newton_with_friction(&p);         break; }
    case 4:  { printf("Combined: \n");                combined_without_friction(&p);    break; }
    case 5:  { printf("Combined with friction:\n");   combined_with_friction(&p);       break; }
    default: { printf("Metodo no valido.\n"); }
  }

  return 0;
}
