// robust_prune.h
#ifndef ROBUST_PRUNE_H
#define ROBUST_PRUNE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Create edge of graph (int: neighbor and float: distance)
using edge = pair<int, float>;

// robustPrune.h
std::vector<std::vector<edge>> RobustPrune(int p, std::vector<int>& V, float a, int R, std::vector<std::vector<edge>>& graph, const std::vector<std::vector<float>>& data);


vector<vector<edge>> CreateGraph(const vector<vector<float>>& data, int size, int R);

#endif