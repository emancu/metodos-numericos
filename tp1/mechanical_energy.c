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
      case 'f': { p.f = atof(optarg);               break; }
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
  double a;

  printf("No Friction: \n");

  primer_impacto = zero_bisection(p, &position);
  primer_impacto.speed = speed(p, primer_impacto.zero);

  for(a= 0; a <= primer_impacto.zero; a+=.5){
    printf(" Instante %.15lf => E: %.15lf, Pos: %.15lf \n",a, mechanical(p,a ), position(p,a));
  }

  // Preparamos para el segundo impacto

  p->h = 0;
  p->v = -primer_impacto.speed;
  p->b = 100; // El segundo impacto ocurre antes del 100. Como no sabiamos como calcularlo, en las consultas nos permitieron hardcodearlo.

  segundo_impacto = zero_bisection(p, &position);
  segundo_impacto.speed = speed(p, segundo_impacto.zero);

  printf(" 1 Impacto \n");
  for(a= 0; a <= segundo_impacto.zero; a+=.5){
    printf(" Instante %.15lf => E: %.15lf, Pos: %.15lf \n",a + primer_impacto.zero, mechanical(p,a ), position(p,a));
  }

  // Preparamos para ver mas alla del 2 impacto
  p->v = -segundo_impacto.speed;

  printf(" 2 Impacto \n");
  for(a= 0; a <= 2; a+=.5){
    printf(" Instante %.15lf => E: %.15lf, Pos: %.15lf \n",a + primer_impacto.zero + segundo_impacto.zero, mechanical(p,a), position(p,a));
  }

}

/*
 * Energia mecanica considerando la friccion, alpha != 0
 */

void friction(Params *p){
  Result primer_impacto, segundo_impacto;
  double a;

  printf("With Friction: \n");

  primer_impacto = zero_bisection(p, &position_with_friction);
  primer_impacto.speed = speed_with_friction(p, primer_impacto.zero);

  for(a= 0; a <= primer_impacto.zero; a+=.5){
    printf(" Instante %.15lf => E: %.15lf, Pos: %.15lf \n",a, mechanical_with_friction(p,a ), position_with_friction(p,a));
  }

  p->h = 0;
  p->v = -primer_impacto.speed * p->f;
  p->b = 50;

  segundo_impacto = zero_bisection(p, &position_with_friction);
  segundo_impacto.speed = speed_with_friction(p, segundo_impacto.zero);
  printf(" 1 Impacto \n");
  for(a= 0; a <= segundo_impacto.zero; a+=.5){
    printf(" Instante %.15lf => E: %.15lf, Pos: %.15lf \n", a + primer_impacto.zero, mechanical_with_friction(p,a ), position_with_friction(p, a));
  }

  p->h = 0;
  p->v = -segundo_impacto.speed * p->f;

  printf(" 2 Impacto \n");
  // Para ver que pasa un poquito despues del segundo impacto
  for(a= 0; a <= 2; a+=.5){
    printf(" Instante %.15lf => E: %.15lf, Pos: %.15lf \n", a + primer_impacto.zero + segundo_impacto.zero, mechanical_with_friction(p,a), position_with_friction(p,a));
  }

}
