#include <stdio.h>
#include <unistd.h>
#include <tipos.h>
#include <bisection.h>
#include <newton.h>

/*
 *  Main
 */

void no_friction(Params *p);
void friction(Params *p);

int main(int argc, char* argv[]){
  // Aca se asignan los params parseados del CLI al estilo -h <valor> -v <valor>
  static const char *optString = "M:h:v:t:m:c:i:a:b:f:x:z:";
  int method, c;
  char * pEnd;
  Params p;

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
      case 'f': { p.f = TFloat(atof(optarg),T);                       break; }
      case 'x': { p.x = TFloat(atof(optarg),T);                       break; }
      case 'z': { p.tol_newton = TFloat(atof(optarg),T);              break; }
      default:  { printf("Cannot parse.\n"); }
    }
  }

  switch(method) {
    case 0:  { no_friction(&p); break; }
    case 1:  { friction(&p); break; }
    default: { printf("Metodo no valido.\n"); }
  }

  return 0;
}

void no_friction(Params *p){
  Result res;
  TFloat a, e, tiempoFinal = TFloat();
  int cantidad_impactos = 0;

  TFloat e0 = mechanical(p,0);
  printf("Energia inicial %.15lf \n", e0.dbl());

  do{
    // res = zero_bisection(p, &position_with_friction);
    res = zero_newton(p, &position, &speed);
    res.speed = speed(p, res.zero);


    cantidad_impactos++;
    tiempoFinal = tiempoFinal + res.zero;
    e = mechanical(p, res.zero);

    mechanical_energy_output(tiempoFinal, mechanical(p, res.zero ), position(p,res.zero));

    p->h = 0;
    p->v = res.speed * -1 * p->f;

  } while(!  (e < e0 / 1000) );

  printf("Cantidad impactos %d Tiempo final %.15lf \n", cantidad_impactos, tiempoFinal.dbl());

}

/*
 * Energia mecanica considerando la friccion, alpha != 0
 */

void friction(Params *p){
  Result res;
  TFloat a, e, tiempoFinal = TFloat();
  int cantidad_impactos = 0;

  TFloat e0 = mechanical_with_friction(p,0);
  printf("Energia inicial %.15lf \n", e0.dbl());

  do{
    // res = zero_bisection(p, &position_with_friction);
    res = zero_newton(p, &position_with_friction, &speed_with_friction);
    res.speed = speed_with_friction(p, res.zero);


    cantidad_impactos++;
    tiempoFinal = tiempoFinal + res.zero;
    e = mechanical_with_friction(p, res.zero);

    mechanical_energy_output(tiempoFinal, mechanical_with_friction(p, res.zero ), position_with_friction(p,res.zero));

    p->h = 0;
    p->v = res.speed * -1 * p->f;

  } while(!  (e < e0 / 10000) );

  printf("Cantidad impactos %d Tiempo final %.15lf \n", cantidad_impactos, tiempoFinal.dbl());

}
