#ifndef FILTEREDVAMANA_H
#define FILTEREDVAMANA_H

#include "medoid.h"
#include "cleandata.h"
#include "FilteredGreedySearch.h"
#include "FilteredRobustPrune.h"
#include "print.h"


// Filtered Vamana Indexing algorithm, returns a directed graph with out-degree <= R
vector <graph> FilteredVamana(vector<vector<float>> &nodes, float a, int L, int R, vector<Map> &STf);

// Function to create a random permutation of data
vector<int> random_permutation(const vector<vector<float>>& data);

#endif