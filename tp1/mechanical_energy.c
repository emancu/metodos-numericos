#include <stdio.h>
#include <unistd.h>
#include <tipos.h>
#include <bisection.h>

/*
 *  Main
 */

void no_friction(Params *p);
void friction(Params *p);

int main(int argc, char* argv[]){
  // Aca se asignan los params parseados del CLI al estilo -h <valor> -v <valor>
  static const char *optString = "M:h:v:t:m:c:i:a:b:f:";
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
  Result primer_impacto, segundo_impacto;
  TFloat a;

  printf("No Friction: \n");

  primer_impacto = zero_bisection(p, &position);
  primer_impacto.speed = speed(p, primer_impacto.zero);

  for(a= 0; a < primer_impacto.zero; a = a + .5){
    mechanical_energy_output(a, mechanical(p,a ), position(p,a));
  }

  // Preparamos para el segundo impacto

  p->h = 0;
  p->v = primer_impacto.speed * -1;
  p->b = 100; // El segundo impacto ocurre antes del 100. Como no sabiamos como calcularlo, en las consultas nos permitieron hardcodearlo.

  segundo_impacto = zero_bisection(p, &position);
  segundo_impacto.speed = speed(p, segundo_impacto.zero);

  printf(" 1 Impacto \n");
  for(a= 0; a < segundo_impacto.zero; a = a + .5){
    mechanical_energy_output(a + primer_impacto.zero, mechanical(p,a ), position(p,a));
  }

  // Preparamos para ver mas alla del 2 impacto
  p->v = segundo_impacto.speed * -1;

  printf(" 2 Impacto \n");
  for(a= 0; a < 2; a = a + .5){
    mechanical_energy_output(a + primer_impacto.zero + segundo_impacto.zero, mechanical(p,a), position(p,a));
  }

}

/*
 * Energia mecanica considerando la friccion, alpha != 0
 */

void friction(Params *p){
  Result primer_impacto, segundo_impacto;
  TFloat a;

  printf("With Friction: \n");

  primer_impacto = zero_bisection(p, &position_with_friction);
  primer_impacto.speed = speed_with_friction(p, primer_impacto.zero);

  for(a= 0; a < primer_impacto.zero; a=a+.5){
    mechanical_energy_output(a, mechanical_with_friction(p,a ), position_with_friction(p,a));
  }

  p->h = 0;
  p->v = primer_impacto.speed * -1 * p->f;
  p->b = 50;

  segundo_impacto = zero_bisection(p, &position_with_friction);
  segundo_impacto.speed = speed_with_friction(p, segundo_impacto.zero);
  printf(" 1 Impacto \n");
  for(a= 0; a < segundo_impacto.zero; a= a+.5){
    mechanical_energy_output(a + primer_impacto.zero, mechanical_with_friction(p,a ), position_with_friction(p, a));
  }

  p->h = 0;
  p->v = segundo_impacto.speed * -1 * p->f;

  printf(" 2 Impacto \n");
  // Para ver que pasa un poquito despues del segundo impacto
  for(a= 0; a < 2; a = a + .5){
    mechanical_energy_output(a + primer_impacto.zero + segundo_impacto.zero, mechanical_with_friction(p,a), position_with_friction(p,a));
  }

}
