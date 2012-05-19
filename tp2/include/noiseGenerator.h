#ifndef __NOISE__
#define __NOISE__
#include <types.h>

void createWithSaltPeperNoise(double * , double, double , char*, PGMInfo* );

void createGaussianNoise(double*,int,char*, PGMInfo*);

#endif
