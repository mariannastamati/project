#ifndef FILTEREDROBUSTPRUNE_H
#define FILTEREDROBUSTPRUNE_H

#include "cleandata.h"
#include "graph.h"

vector <graph> FilteredRobustPrune(int currentPoint, vector<int>& visited_nodes, float a, int R, vector<graph>& G, const vector<vector<float>>& data);

#endif