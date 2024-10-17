#ifndef VAMANAINDEXING_H
#define VAMANAINDEXING_H

#include <iostream>
#include <vector>
#include <random>

#include "graph.h"

using namespace std;

// Vamana Indexing Algorithm
vector<vector<edge>> VamanaIndexing(const vector<vector<float>>& data, int size, int R);

#endif