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
std::vector<std::vector<edge>> RobustPrune(int p, std::vector<int>& V, float a, int R, 
    std::vector<std::vector<edge>>& graph, const std::vector<std::vector<float>>& data);

#endif