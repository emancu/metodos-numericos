#ifndef __TOOLS__
#define __TOOLS__
#include <types.h>

void print_pretty_matrix(Matrix, PGMInfo*);
void print_results(double*, PGMInfo*, bool);

void create_new_picture(double*, char*, PGMInfo*);
PGMInfo parse_pgm(char*,int);
void free_pixels_memory(PGMInfo*);

double psnr(char* original, char* noisy);
void print_pgm_info(PGMInfo* pgm_info);


#endif
