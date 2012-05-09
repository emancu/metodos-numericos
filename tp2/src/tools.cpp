#include <tools.h>

void print_matrix(Matrix* matrix){
  Matrix::iterator row;
  for(row = matrix->begin(); row != matrix->end(); row++){
    printf("row: %d\n", row->first);
    Row::iterator pair;
    for(pair = row->second.begin(); pair != row->second.end(); pair++){
      printf("  position: %d\n",   pair->first);
      printf("  value   : %.5f\n", pair->second);
    }
    printf("\n");
  }
}

void print_lower_bands(LowerBands* lower_bands){
  LowerBands::iterator lower_band;
  for(lower_band = lower_bands->begin(); lower_band != lower_bands->end(); lower_band++){
    printf("lower band for column %d\n", lower_band->first);
    list<int>::iterator row;
    for(row = lower_band->second.begin(); row != lower_band->second.end(); row++){
      printf(" %d ", *row);
    }
    printf("\n");
  }
}

void print_results(double* results, int size){
  for(int i = 0; i < size; i++){
    printf("%.5f ", results[i]);
    if(i % size == 0) printf("\n");
  }
}
