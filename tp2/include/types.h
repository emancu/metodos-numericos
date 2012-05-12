#ifndef __TYPES__
#define __TYPES__
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <map>
#include <set>

using namespace std;
typedef map<int, double> Row;
typedef map<int, Row> Matrix;
typedef map<int, set<int> > LowerBands;

#endif
