#ifndef __TOOLS__
#define __TOOLS__
#include <types.h>

void print_matrix(Matrix*);
void print_pretty_matrix(Matrix* matrix);
void print_lower_bands(LowerBands*);
void print_results(double*, int, bool);
void insert_row_number(LowerBands*, int, int);

void create_new_picture(double*,char*,int);
PGMInfo parse_pgm(char*);
void free_pixels_memory(PGMInfo*);


#endif
