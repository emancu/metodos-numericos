#include <tools.h>

void print_matrix(Matrix* matrix){
  Matrix::iterator row;
  for(row = matrix->begin(); row != matrix->end(); row++){
    printf("row: %d\n", row->first);
    Row::iterator pair;
    for(pair = row->second.begin(); pair != row->second.end(); pair++){
      printf("  position: %d\n",   pair->first);
      printf("  value   : %.5f\n", pair->second);
      // printf("%.5f ", pair->second);
      // if(pair->first % matrix->size() == matrix->size() - 1) printf("\n");
    }
    printf("\n");
  }
}

void print_lower_bands(LowerBands* lower_bands){
  LowerBands::iterator lower_band;
  for(lower_band = lower_bands->begin(); lower_band != lower_bands->end(); lower_band++){
    printf("lower band for column %d\n", lower_band->first);
    set<int>::iterator row;
    for(row = lower_band->second.begin(); row != lower_band->second.end(); row++){
      printf(" %d ", *row);
    }
    printf("\n");
  }
}

void print_results(double* results, int size, bool verification){
  for(int i = 0; i < size; i++){
    if(verification){
      unsigned int color = (unsigned int) results[i];
      if(0 <= color && color < 256)
        printf(".");
      else
        printf("F variable %d is %d", i, color);
    }else{
      printf("%.5f ", results[i]);
    }

    if(i % size == size - 1) printf("\n");
  }
}

void insert_row_number(LowerBands* lower_bands, int row_number, int column_number){
  // If there's no set for that column, make one.
  //if(lower_bands->count(column_number) == 0){
  //  set<int> rows;
  //  (*lower_bands)[column_number] = rows;
  //}
  (*lower_bands)[column_number].insert(row_number);
}
