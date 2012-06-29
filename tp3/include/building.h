#ifndef __BUILDING__
#define __BUILDING__

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <matrix.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

class Building {

  public:
    Building();
    Building(char*);
    ~Building();

    /*
     * Metodos que modifican self
     */
    void generate_matrix();
    void randomize();
    void swap_or_move_heavy_light_cars();
    void move_heavy_car();
    void move_all_light_cars();
    void move_all_heavy_cars();

    /*
     * Metodos que NO modifican self
     */
    Matrix* matrix() const;
    void print() const;
    void output_file(char*) const;
    int distance_to(const Building&) const;

    /*
     * Getters
     */
    int amount_heavy_cars() const;
    int amount_light_cars() const;

  private:
    int _floors;
    int _floor_mass;
    int _light_car_mass;
    int _heavy_car_mass;
    int _light_cars_amount;
    int _heavy_cars_amount;
    int _moves;

    int _light_cars_stack;
    int _light_car_to;
    int _heavy_cars_stack;
    int _heavy_car_to;

    int *_light_cars_array;
    int *_heavy_cars_array;
    int *_coefficients;

    Matrix *_matrix;

};

#endif
