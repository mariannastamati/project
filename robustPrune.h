// robust_prune.h
#ifndef ROBUST_PRUNE_H
#define ROBUST_PRUNE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "graph.h"

using namespace std;

// robustPrune.h
std::vector<std::vector<edge>> RobustPrune(int p, std::vector<int>& V, float a, int R, std::vector<std::vector<edge>>& graph, const std::vector<std::vector<float>>& data);

#endif