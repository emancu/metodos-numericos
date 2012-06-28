#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]){
  srand(time(NULL));
  int floors = (rand() % 20) + 1;
  int number_light_cars = (rand() % 200) + 1;
  int number_heavy_cars = (rand() % 200) + 1;

  int *light_cars_array = new int[floors];
  int *heavy_cars_array = new int[floors];
  int *coefficients     = new int[floors];

  for(int i = 0; i < floors; i++)
    coefficients[i] = (rand() % 300) + 50000;

  int amount_light = number_light_cars;
  int amount_heavy = number_heavy_cars;
  for(int i = 0; i < floors - 1; i++) {
    light_cars_array[i] = rand() % (amount_light + 1);
    heavy_cars_array[i] = rand() % (amount_heavy + 1);

    amount_light -= light_cars_array[i];
    amount_heavy -= heavy_cars_array[i];
  }
  light_cars_array[floors - 1] = amount_light;
  heavy_cars_array[floors - 1] = amount_heavy;

  ofstream file;
  file.open("randbuil");

  file << floors << " " << 20000 << " " << 500 << " " << 1000 << endl;

  for(int i = 0; i < floors; i++){
    file << coefficients[i];
    if(i == floors - 1)
      file << endl;
    else
      file << " ";
  }

  for(int i = 0; i < floors; i++){
    file << light_cars_array[i];
    if(i == floors - 1)
      file << endl;
    else
      file << " ";
  }

  for(int i = 0; i < floors; i++){
    file << heavy_cars_array[i];
    if(i == floors - 1)
      file << endl;
    else
      file << " ";
  }

  file.close();

  return 0;
}

