// robust_prune.h
#ifndef ROBUST_PRUNE_H
#define ROBUST_PRUNE_H

#include <fstream>
#include <string>
#include <limits>
#include <unordered_set>

#include "graph.h"
#include "printGraph.h"

using namespace std;

// Robust Prune Algorithm
vector<vector<edge>> RobustPrune(int p, vector<int>& V, float a, int R, 
    vector<vector<edge>>& graph, const vector<vector<float>>& data);

#endif