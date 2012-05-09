#ifndef __TYPES__
#define __TYPES__
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <map>
#include <list>

using namespace std;
typedef map<int, double> Row;
typedef map<int, Row> Matrix;
typedef map<int, list<int> > LowerBands;

#endif
