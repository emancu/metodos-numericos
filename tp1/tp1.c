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
  static const char *optString = "M:h:v:t:m:c:i:a:b:x:z:";
  int method, c;
  Params p;

  while((c = getopt(argc, argv, optString)) != -1){
    switch(c){
      case 'M': { method = atoi(optarg);            break; }
      case 'h': { p.h = atof(optarg);               break; }
      case 'v': { p.v = atof(optarg);               break; }
      case 't': { p.tol_bisect = atof(optarg);      break; }
      case 'm': { p.mass = atof(optarg);            break; }
      case 'c': { p.cr = atof(optarg);              break; }
      case 'i': { p.max_iterations = atoi(optarg);  break; }
      case 'a': { p.a = atof(optarg);               break; }
      case 'b': { p.b = atof(optarg);               break; }
      case 'x': { p.x = atof(optarg);               break; }
      case 'z': { p.tol_newton = atof(optarg);      break; }
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
