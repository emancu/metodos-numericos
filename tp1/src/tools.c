#include <tools.h>

bool stopping_criteria(TFloat a, TFloat b, TFloat tolerance){
  return TFloat(fabs((a - b).dbl()),T) < tolerance;
}

TFloat speed(Params *p, TFloat time){
  return p->v - GRAVITY*time;
}

TFloat position(Params *p, TFloat time){
  TFloat h = p->h;
  TFloat v = p->v;
  TFloat dos = TFloat(2,T);
  return h + v*time - GRAVITY*time*time/dos;
}

// Derivada de ecuacion (2) - Aceleracion
TFloat acceleration(Params *p, TFloat time) {
  return GRAVITY*-1;
}

/*
 * With friction
 */

TFloat position_with_friction(Params *p, TFloat time) {
  TFloat h = p->h;
  TFloat v = p->v;
  TFloat alpha = p->cr/p->mass;
  TFloat e = (alpha * -1 * time).exponencial();
  return h + v/alpha + GRAVITY/(alpha*alpha) - GRAVITY*time/alpha - (v/alpha + GRAVITY/(alpha*alpha)) * e;
}

TFloat speed_with_friction(Params *p, TFloat time) {
  TFloat alpha = p->cr/p->mass;
  TFloat v = p->v;
  TFloat e = (alpha * -1 * time).exponencial();
  return (GRAVITY*-1)/alpha + ( v + GRAVITY/alpha) * e;
}

// Derivada de ecuacion (4) - Aceleracion
TFloat acceleration_with_friction(Params *p, TFloat time) {
  TFloat alpha = p->cr/p->mass;
  TFloat v = alpha * p->v;
  TFloat e = (alpha * -1 * time).exponencial();
  return (v - GRAVITY) * e;
}

/*
 * Asserts
 */

void assert_intervals(TFloat (*fn)(Params *, TFloat), Params *p) {
  TFloat a = p->a, b = p->b;
  if (fn(p,a) * fn(p,b) > TFloat(0,T)){
    printf("-----Los bordes del intervalo no cumplen las condiciones.-----\n");
    printf("Valor a (%lf) => f(a) = %lf ; valor b (%lf) => f(b) = %lf \n\n", a.dbl(), fn(p, a).dbl(), b.dbl(), fn(p, b).dbl() );
    exit(1);
  }

}
