#include <combinated.h>


void combinated_without_friction(Params* p){
  combinated(p, &position, &speed, &acceleration);
}

void combinated_with_friction(Params* p){
  combinated(p, &position_with_friction, &speed_with_friction, &acceleration_with_friction);
}

/*
 * Auxiliar
 */

void combinated(Params* p, TFloat (*fn_pos)(Params *, TFloat), TFloat (*fn_speed)(Params*, TFloat), TFloat (*fn_accel)(Params*, TFloat) ) {
  Result res;
  TFloat instant = 0;


  // Primer impacto
  res = zero_bisection(p, fn_pos); // Nos acercamos con bisection
  if(res.iterations == p->max_iterations){
    printf("  BISECCION :SALIO POR ITERACIONES MAXIMAS!!! = %lu \n", p->max_iterations);
  } else{
    printf("  BISECCION :CANT ITERACIONES = %lu \n", res.iterations);
  }

  // Solo actualizamos el punto inicial para Newton
  p->x = res.zero;
  res = zero_newton(p, fn_pos, fn_speed);
  instant = instant + res.zero;
  printf("  Primer impacto  = %.15lf al instante: %.15lf. Velocidad final = %.15lf \n", fn_pos(p, res.zero).dbl(), instant.dbl(), res.speed.dbl());
  if(res.iterations == p->max_iterations){
    printf("  SALIO POR ITERACIONES MAXIMAS!!! = %lu \n", p->max_iterations);
  } else{
    printf("  CANT ITERACIONES = %lu \n", res.iterations);
  }

/*
  // Altura Maxima
  p->h = 0;
  p->b = 100 ; // FIXME: ver este tema del intervalo que es bastante sensible!!!!!!!!!
  p->v = -res.speed;
  res = zero_bisection(p, fn_speed); // Nos acercamos con bisection

  p->x = res.zero;

  res = zero_newton(p, fn_speed, fn_accel);
  printf("Altura %lf \n", fn_pos(p, res.zero));

  // Segundo impacto

  res = zero_bisection(p, fn_pos); // Nos acercamos con bisection
  p->x = res.zero;
  zero_newton(p, fn_pos, fn_speed);
*/
}