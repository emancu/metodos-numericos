#include <tools.h>

/*
 * General
 */

bool stopping_criteria(TFloat a, TFloat b, TFloat tolerance){
  return TFloat( fabs((a - b).dbl()), T) < tolerance;
}

void output(int op, TFloat x, TFloat instant, TFloat speed) {
  switch(op){
    case 0: { printf("  Primer impacto = ");  break; }
    case 1: { printf("  Altura Maxima = ");   break; }
    case 2: { printf("  Segundo impacto = "); break; }
  }

  printf("%.15lf al instante: %.15lf. Velocidad final = %.15lf \n", x.dbl(), instant.dbl(), speed.dbl());
}

void mechanical_energy_output(TFloat instant, TFloat e, TFloat pos) {
  printf(" Instante %.15lf => E: %.15lf, Pos: %.15lf \n", instant.dbl(), e.dbl(), pos.dbl());
}

/*
 * Without friction
 */

TFloat speed(Params *p, TFloat time){
  return p->v - GRAVITY*time;
}

TFloat position(Params *p, TFloat time){
  TFloat h = p->h;
  TFloat v = p->v;
  return h + v*time - GRAVITY*time*time/2;
}

// Derivada de ecuacion (2) - Aceleracion
TFloat acceleration(Params *p, TFloat time) {
  return GRAVITY * -1;
}

TFloat mechanical(Params *p, TFloat time) {
  TFloat d = speed(p, time);
  return GRAVITY * position(p,time) + d*d/2.0;
}


/*
 * With friction
 */

TFloat position_with_friction(Params *p, TFloat time) {
  TFloat h = p->h;
  TFloat v = p->v;
  TFloat alpha = p->cr/p->mass;
  TFloat e = ( alpha * time * -1).exponencial();
  return h + v/alpha + GRAVITY/(alpha*alpha) - GRAVITY*time/alpha - (v/alpha + GRAVITY/(alpha*alpha)) * e;
}

TFloat speed_with_friction(Params *p, TFloat time) {
  TFloat alpha = p->cr/p->mass;
  TFloat v = p->v;
  TFloat e = ( alpha * time * -1).exponencial();
  return GRAVITY *(-1)/alpha + ( v + GRAVITY/alpha) * e;
}

// Derivada de ecuacion (4) - Aceleracion
TFloat acceleration_with_friction(Params *p, TFloat time) {
  TFloat alpha = p->cr/p->mass;
  TFloat v = alpha * p->v;
  TFloat e = ( alpha * time * -1).exponencial();

  return (v - GRAVITY) * e;
}

TFloat mechanical_with_friction(Params *p, TFloat time) {
  TFloat d = speed_with_friction(p, time);
  return GRAVITY * position_with_friction(p,time) + d*d/2.0;
}

/*
 * Asserts
 */

void assert_intervals(TFloat (*fn)(Params *, TFloat), Params *p) {
  TFloat a = p->a, b = p->b;
  if (fn(p,a) * fn(p,b) > 0){
    printf("-----Los bordes del intervalo no cumplen las condiciones.-----\n");
    printf("Valor a (%lf) => f(a) = %lf ; valor b (%lf) => f(b) = %lf \n\n", a.dbl(), fn(p, a).dbl(), b.dbl(), fn(p, b).dbl() );
    exit(1);
  }
}
