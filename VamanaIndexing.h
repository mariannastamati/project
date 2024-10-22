#ifndef VAMANAINDEXING_H
#define VAMANAINDEXING_H

#include <iostream>
#include <vector>

#include "graph.h"

using namespace std;

// Vamana Indexing Algorithm
vector<vector<edge>> VamanaIndexing(const vector<vector<float>>& data, int size, int R);

// Function to return sigma (σ), is a random permutation of points 1..n
vector<int> random_permutation(const vector<vector<float>>& data);

#endif