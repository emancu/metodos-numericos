#include <bisection.h>
#include <TFloat.h>
#include <float.h>


void bisection_without_friction(Params* p) {
  bisection(p, &position, &speed,&mechanical_without);
}

void bisection_with_friction(Params* p) {
  bisection(p, &position_with_friction, &speed_with_friction, &mechanical_with_friction);
}

/*
 * Auxiliar
 */

void bisection(Params* p, TFloat (*fn_pos)(Params*,TFloat), TFloat (*fn_speed)(Params*, TFloat),TFloat (*mechanicalToCall)(Params*, TFloat)) {
  TFloat instant = TFloat(0,T);
  Result res;


  // Primer impacto

  res = zero_bisection(p, fn_pos);
  res.speed = fn_speed(p,res.zero);
  instant = instant + res.zero;
  printf("  Primer impacto  = %.15lf al instante: %.15lf. Velocidad final = %.15lf \n", fn_pos(p, res.zero).dbl(), instant.dbl(), res.speed.dbl());
  if(res.iterations == p->max_iterations){
    printf("  SALIO POR ITERACIONES MAXIMAS!!! = %lu \n", p->max_iterations);
  } else{
    printf("  CANT ITERACIONES = %lu , max = %lu\n", res.iterations, p->max_iterations);
  }

  // Altura Maxima
  p->h = 0;
  p->b = 100 ; // FIXME: ver este tema del intervalo que es bastante sensible!!!!!!!!!
  p->v = res.speed * -1;

  res = zero_bisection(p, fn_speed);
  printf("  Altura Maxima   = %.15lf al instante: %.15lf. Velocidad final = %.15lf \n", fn_pos(p,res.zero).dbl(), (instant + res.zero).dbl(), fn_speed(p,res.zero).dbl());

  // Segundo impacto
  res = zero_bisection(p, fn_pos);
  instant = instant + res.zero;
  printf("  Segundo impacto = %.15lf al instante: %.15lf. Velocidad final = %.15lf \n", fn_pos(p, res.zero).dbl(), instant.dbl(), fn_speed(p, res.zero).dbl());


  TFloat mechanical = TFloat();
  int j;
  for (j = 0 ; j <= res.zero.dbl() + 1 ; j++){
    mechanical = mechanicalToCall(p,j);
    printf(" %d, %.15lf  \n ", j, mechanical.dbl());
  }

}

Result zero_bisection(Params *p, TFloat (*fn)(Params *, TFloat)) {
  unsigned long iteracion = p->max_iterations;
  TFloat a = p->a, b = p->b,m;
  Result res;

  assert_intervals(fn, p);

  TFloat cero = TFloat(0,T);
  TFloat dos = TFloat(2,T);

  while( --iteracion > 0 && !stopping_criteria(a,b, p->tol_bisect)) {
    m = (b+a)/dos;
    ( fn(p,a) * fn(p,m) > cero )? a = m : b = m;
    //printf("iteracion = %lu \n" , iteracion);
  }

  res.zero = m;
  res.iterations = p->max_iterations - iteracion;

  return res;
}
