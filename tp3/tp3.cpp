#include <tools.h>
#include <matrix.h>
#include <building.h>

int main(int argc, char* argv[]){
  static const char *optString = "f:e:i:h:o:";
  char *input_path, *output_path;
  double epsilon;
  int c, iterations, heuristic;

  while((c = getopt(argc, argv, optString)) != -1){
    switch(c){
      case 'f': { input_path  = optarg;       break; }
      case 'e': { epsilon     = atof(optarg); break; }
      case 'i': { iterations  = atoi(optarg); break; }
      case 'o': { output_path = optarg;       break; }
      case 'h': { heuristic   = atoi(optarg); break; }
      default:  { printf("Cannot parse.\n"); }
    }
  }

  Building *building = new Building(input_path);
  Matrix *a = building->matrix();
  double *values;
  values = eigenvalues(*a, epsilon, iterations);
  natural_frecuencies(values, a->rows());
  bool moved_light = false;

  while(!is_building_safe(values, a->rows())){
    print_array(values, a->rows());
    switch(heuristic){
      case 0: {
        building->randomize();
        break;
      }
      case 1: {
        building->move_heavy_car();
        break;
      }
      case 2: {
        building->swap_or_move_heavy_light_cars();
        break;
      }
      case 3: {
        building->move_all_light_cars();
        break;
      }
      case 4: {
        building->move_all_heavy_cars();
        break;
      }
      case 5: {
        if(moved_light)
          building->move_all_heavy_cars();
        else
          building->move_all_light_cars();
        moved_light = !moved_light;
        break;
      }
    }

    building->generate_matrix();
    a = building->matrix();
    delete[] values;
    values = eigenvalues(*a, epsilon, iterations);
    natural_frecuencies(values, a->rows());
  }

  building->print();
  building->output_file(output_path);
  // print_array(values, a->rows());

  delete building;
  delete[] values;

  return 0;
}

//                                  ,cccc,,,
//                               ,P"`.`."`.ch$.
//                              .P`.`.`.`.`.`;`h
//                             j'.`.`.`.`.`.`.?3?
//                             $`.`.`.`.`.`.`.`?$.
//                           ,P`.`.`.`.`.`.,$$,.3$h.
//                         ,P`.`.`.`.`.`.,$$$$$i.`$$h
//                       ,P".`.`.`.`.`.,$$$$$$$$$hJ$$$.
//                     c"`.`.`.`.`.,$$$$$$$$$$$$$$$$$$$
//                   J"`.`.`.`.`.;J$$$$$$$$$$$$$$$$$$$$h
//                 J"`.`.`.`.`.,;$$$$$$$$$?????iiJJJJJJ$$$$$cc,
//               J"`.`.`.`.`.`;???????iiJJJJ$$$$$$$$$$$$$$$$$$$$h
//             ,?`.`.`.`.`.`;;J$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$c
//           ,P`.`.`.`.`.`.;;P"$F?$$$$$$$$$?$$"?$I"?C?$$$$$$$$$$$$$h
//          J".`.`.`.`.`.,;;$ j"J$?"""?$C`.??";;J?$'?L$$$$$$$$$$$$$$>
//        ,P.`.`.`.`.`.`,;;$'J3F'J$??$3c$`.`?h$9hP"`.$<?$$$$$$$$$$$$'
//       J"`.`.`.`.`.`.,;9'$ P3`.`.""`.`3`.`.`.`.`.`.3?$ $?$$$$$$$$P
//      J'.`.`.`.`.`.`;;J$,/j'$`.`.`.`.`$`.`.`.`.`.`.3F<? "',_?$$$$    _,,="
//     P.`.`.`.`.`.`.;;J'$$ $ ?`.`.`.`.$"`.`.`.`.`.`.3h ?     `"?$C,c$P"
//    P`.`.`.`.`.`.,;;9' $$ F  h.`.`.`."?".".`.`.`.`.$$  h=-,_     `?c
//  ,$.`.`.`.`.`.`;;;J' ,'$j' <$.`.`.`.`.`.`.`.`.`.`.$j   ?c  ".     `$"??hcc?
// ;C;.`.`.`.`.`;;;;J'$$h;$J  `Ph`.`.`,JllllCCc`.`.`.PjL    "=c,`=c,   "h.
// $;;.`.`.`.`,;;;;P   Jh?$J   L$`.`.`?hiiii?".`.`.`.Fj''       ??  ?.   ?c
// C;;,`.`.`.;;;;9"   $"  $J   $'h.`.`.`.`.`.`.`.`.`JFJ  $C      $   ,>h, `?c,_
// C;;;;;;;;;;;;$    <Lc,jP$   $ ?h`.`.`.`.`.`.`.`J$$ $  $ ?cc,  ?.,P""=c,c=""
// C;;;;;;;;;;;?$    <C,'j'$   $  $?h,.`.`.`.`,J??;$F $  $    $ ""$ . ,=-cc"""
// $;;;;;;;;;;;;?h.  <$F $ $   $  $;;;;?TTTT??;;;;;P  F  $  > $  .`h "c`h.
// $;;;;;;;;;;;;;9h?$C$ J',P   F  $h;;;;;;;;;;;;;;9> j'c $  > ?  `h`h `"c`h.
// $;;;;;;;;;;;;;;h;;;$ $ $ \  F  $$;;;;;;;;;;;;;;9' 3 $ $  h `h  $ ?c"h.3?=,_
// `h;;;;;;;;;;;;;$;;;$j'<$ `h.F  F<C;;;;;;;;;;;;;J> $ $ $  $ `h   $ $Pc,`"?$h.
//  $;;;;;;;;;;;;;??;;P$ $F  h,F  F,c;;;;;;;;;;;;;$> $ $ $  $  C    ?c?c  "???"
//  `h;;;;;;;;;;;;;;;9FF<$   h,F j'J;;;;;;;;;;;;;$ h $ $ ?. $  $   `h`?`h
//   ?;;;;;;;;;;;;;;;$<F$$   F,F $,c;;;;;;;;;`;;J'J3 $ $ `h ?  $h   `h`h.`.
//    $;;;;;;;;;;;;;;FJj'$  .F  Jl$;;;;;;;;;;;;$.P.`,? ?  h `h <$?   ?h `$C3hc
//     $;;;;;;;;;;;;J $$ $  J'  $ $;;;;;;;;;'J"3" $,'? ?. $  $  $'L   $"',"","
//      "i;;;;;;;;;;$j'$ $  $  J',C;;`;;;ii?3$'J $ $ `L`h `h ?. `h'L  .?,_
//       `i;;;;;;;;;$$$L ?',F .P $.`.`.j??$cc,' J' F  $ $  $  ?   $ ?c`-,,h.
//        ?;;;;;;;;;;;$$?c$F  P J'.`.`.`.`.`P" ,F `F  ? `h `h  h   $  ???
//        `C;;;;;;;;;;;$>    / J'`.`.`.`.`.??3FJF  $   L $  `h `h  c$$.
//         $;;;;;;;;;;;$,?,-<c$`.`.`.`.`.`.`.`$F$c `h  `h_$  `L  $???"`$
//         $;;;;;;;;;;;'"$ $?$.`.`.`.`.`.`.`.`?`.`?$$.    `?c,$$,`L`.`.`h
//         $;;;;;;;;;;`.?LP'`?.`.`.`.`.`.`.`.`.`.`.`.`?c,    $$F.`.`.`.`3
//         <h;;;;;;;;`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.?$?cJ;,.`.`.`.`3>
//         <C;;;;;;;.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.;;;.`.`.`.`3'
//         <C;C;;;;`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.;;;,`.`.`.`J
//         <C9C;;;;`.c???i.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`;;;;;`.`.`.`$
//         <C9;;;;.`$;ii;?h`.`.`.`,;;;.`.`.`.`.`.`.`.`.`.`.`J;;;;`.`.`.`F
//         <;9;;;;.<C?b9h;P`.`.`.,;3;;.`.`.`.`.`.`.`.`.`.`.`?;;;;`.`.`.j'
//         <29h;;;;`$;;;;$.`.`.`;;;$;;.`.`.`.`.`.`.`.`.`.`.`.L;;;`.`.`.$
//         `C;h;;;;`.?ii?`.`.,;;;;J?;`.`.`.`.`.`.`.`j???hc.`.h;;.`.`.`;P
//          $;9h;;;;;`.`.`.;;;;;;I?;;`.;;;,`.`.`.`.jF;$?h?h`.$;;.`.`.`F
//          $;;?i;;;;;;;;;;;;;;;J?;;.`;;;;;;;`.`.`.?C?bi$;$`.$;;.`.`.$
//          3;;;;$i;;;;;;;;;;;J?;;;`.`.;;h;;;;;`.`.`?i;;;J'`.$;;.`.`J'
//          `C;;;;??hiiiiiiJ??;;;;.`.`.;;?h;;;;;;`.`.`"""`.`;P;;.`.`F
//           h;;;;;;;;;;;;;;;;;`.`.`.`.`.;;$i;;;;;;;;`.`;;;;J;;;.`.j'
//           $;;;;.`.`.`.`.`.`.`.`.`.`.`.`;;;$i;;;;;;;;;;;;$;;;`.`.3
//           <;;;;.`.`.`.`.`.`.`.`.`.`.`.`.;;;;?$iijjjjii$?;;;;`.`.3
//           `C;;`.`.`.`.`.`.`.`.`.`.`.`.`.`.`;;;;;;;;;;$;;;;;;`.`.J
//            $;;`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`;;;;;;;;C;;;;;.`.`.$
//            ?;.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`;;;;;9;;;;;;.`.`.3
//            `h.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`;;;$;;;;;`.`.`.3
//             h.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.;;$;;;;;`.`.`.3
//             ?.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`;?C;;;;`.`.`.3
//             `h`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`$;;;;`.`.`.?,
//              $`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.h;;.`.`.`.`$
//              ?,.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.?h;.`.`.`.`.h
//               $.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`?h;`.`.`.`.`h
//               `h`.`.`.`.`.`.`.`.`.`;;.`.`.`.`.`.`.`.`.`.`h;,`.`.`.`.h
//                $`.`.`.`.`.`.`.`.`.`;;.`.`.`.`.`.`.`.`.`.`.$;;.`.`.`.`L
//                ?`.`.`.`.`.`.`.`.`.`;;.`.`.`.`.`.`.`.`.`.`.`?i;`.`.`.`?,
//                `h.`.`.`.`.`.`.`.`.`;;.`.`.`.`.`.`.`.`.`.`.`.`h;,`.`.`.?.
//                 h.`.`.`.`.`.`.`.`.`t$h`.`.`.`.`.`.`.`.`.`.`.``h;;.`.`.`?
//                 $.`.`.`.`.`.`.`.`.`3$$`.`.`.`.`.`.`.`.`.`.`.`.`h;;;.`.`.h
//                 $.`.`.`.`.`.`.`.`.`."'`.`.`.`.`.`.`.`.`.`.`.`.`.$;;;;.`.`h
//                 $.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`?;;;;`.`.h
//                 ?,`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.$;;;;.`.`$.
//                 `h`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`?;;;;`.`.?.
//                  $`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`,c=""'"""`.`.`.`?
//                  $`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`/".`.`.`.`.`.`.`.`3
//                  $`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`/".`.,c$h`.`.`.`.`.`3
//                  F`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.$c,=="`.`"h.`.`.`.`.`3
//                 ;F`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`$?.`.`.`.`P
//                 $.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.z?`.`.`.`.j'
//                .F.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.,cP"`.`.`.`.`.$
//                ;F.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.,,c=="`.`.`.,,c.`.`j'
//                3`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.("`.`.`.`.,c="`.`.`.`$
//                ?`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`=ccc????"`.`.,,=.`.`F
//                `h.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.`.("`.`.`_,,c=$F`.`;`.$'
//                 h;`.`.`.`.`.`.`.`.`.`L`.`.`.`.`,;;;;i.`"""""`.`.,=".`.J'`.$>
//                 $;,.`.`.`.`.`.`.`.`.`.h;;;;;;;;;;;;;$.`.`.`.`,,='.`.,?$.`J'h
//                 `C;.`.`.`.`.`.`.`.`.`.`$;;;;;;;;;;;;F.`.`.,r".`,,=""'J'.3F`$
//                  $;;`.`.`.`.`.`.`.`.`.`.?i;;;;;;;;;$`.`.`.?,c=".`.`.`P`,F.`$
//                  `h;;.`.`.`.`.`.`.`.`.`.`.h;;;;;;;J'`.`.`.`.`.`.`.`.3.`P`.`F
//                   h;;;`.`.`.`.`.`.`.`.`.`.`?;;;;;;F.`.`.`.`.`.`.`.`.?,J.`.;F
//                   ?;;;;.`.`.`.`.`.`.`.`.`.`.?;;;;$`.`.`.`.`.`.`.`.`.`.`.`.3'
//                   `h;;;;`.`.`.`.`.`.`.`.`.`.`$;;$.`.`.`.`.`.`.`.`.`.`.`.`.$
//                    ?;;;;`.`.`.`.`.`.`.`.`.`.`."$'.`.`.`.`.`.`.`.`.`.`.`.`.$
//                    `C;;;;.`.`.`.`.`.`.`.`.`.`.`?i.`.`.`.`.`.`.`.`.`.`.`.`.P
//                     ?;;;;;`.`.`.`.`.`.`.`.`.`.`.?;`.`.`.`.`.`.`.`.`.`.`.`j'
//                     `C;;;;,.`.`.`.`.`.`.`.`.`.`.`?;.`.`.`.`.`.`.`.`.`.`.`$
//                      ?;;;;;;`.`.`.`.`.`.`.`.`.`.`.?;`.`.`.`.`.`.`.`.`.`.`$
