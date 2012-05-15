#ifndef __TOOLS__
#define __TOOLS__
#include <types.h>

void print_pretty_matrix(Matrix, PGMInfo*);
void print_results(double*, int, bool);

void create_new_picture(double*, char*, PGMInfo*);
PGMInfo parse_pgm(char*);
void free_pixels_memory(PGMInfo*);


#endif
