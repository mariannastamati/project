#ifndef VAMANAINDEXING_H
#define VAMANAINDEXING_H

#include "graph.h"
#include "GreedySearch.h"
#include "robustPrune.h"

using namespace std;

// Vamana Indexing Algorithm
vector<vector<edge>> VamanaIndexing(const vector<vector<float>>& data, float a, int L, int R, int& s);

// Function to return sigma (σ), is a random permutation of points 1..n
vector<int> random_permutation(const vector<vector<float>>& data);

#endif