#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <vector>

#include "medoid.h"

using namespace std;

// Function to print 2D data
void PrintData(vector<vector<float>> &data);

// Function to print Medoid Map
void PrintMedoidMap(vector<Map> &M); 

#endif