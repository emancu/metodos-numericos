#include <stdlib.h>
#include <sstream>
#include <stdio.h>


int main(int argc, char* argv[]){
  static const char *optString = "o:l:f:r:";
  int c;
  char* input;
  char* output;
  double lambda;
  

  while((c = getopt(argc, argv, optString)) != -1){
    switch(c){
      case 'l': { lambda  = atof(optarg); break; }
      default:  { printf("Cannot parse.\n"); }
    }
  }


	printf("tp3 \n");

  return 0;
}
