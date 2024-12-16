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

// Function to print graph G (Graph created from Filtered or Stitched Vamana)
void PrintGraph(const vector<graph> &G);

#endif