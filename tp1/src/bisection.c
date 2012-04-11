#include <bisection.h>
#include <TFloat.h>
#include <float.h>


void bisection_without_friction(Params* p) {
  bisection(p, &position, &speed);
}

void bisection_with_friction(Params* p) {
  bisection(p, &position_with_friction, &speed_with_friction);
}

/*
 * Auxiliar
 */

void bisection(Params* p, TFloat (*fn_pos)(Params*,TFloat), TFloat (*fn_speed)(Params*, TFloat)) {
  TFloat instant = TFloat(0,T);
  //TFloat instant = 0;
  Result res;

  // Primer impacto
  res = zero_bisection(p, fn_pos);
  res.speed = fn_speed(p,res.zero);
  instant = instant + res.zero;
  printf("  Primer impacto  = %.15lf al instante: %.15lf. Velocidad final = %.15lf \n", fn_pos(p, res.zero).dbl(), instant.dbl(), res.speed.dbl());
  if(res.iterations == p->max_iterations){
    printf("  SALIO POR ITERACIONES MAXIMAS!!! = %lu \n", p->max_iterations);
    printf("  tolerance %.15lf\n",(p->tol_bisect).dbl());
  } else{
    printf("  CANT ITERACIONES = %lu , max = %lu\n", res.iterations, p->max_iterations);
    printf("  tolerance %.15lf\n",(p->tol_bisect).dbl());
  }



/*
  // Altura Maxima
  p->h = 0;
  p->b = 100 ; // FIXME: ver este tema del intervalo que es bastante sensible!!!!!!!!!
  p->v = -res.speed;
  instant += res.zero;
  res = zero_bisection(p, fn_speed);
  printf("  Altura Maxima   = %lf al instante: %lf. Velocidad final = %lf \n", fn_pos(p,res.zero), instant, fn_speed(p,res.zero));

  // Segundo impacto
  zero_bisection(p, fn_pos);
  instant += res.zero;
  printf("  Segundo impacto = %lf al instante: %lf. Velocidad final = %lf \n", fn_pos(p, res.zero), instant, fn_speed(p, res.zero));
  */
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
