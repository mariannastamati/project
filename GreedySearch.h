#ifndef GREEDY_SEARCH_H
#define GREEDY_SEARCH_H

#include "graph.h"
#include <set>
#include <algorithm>


using namespace std; 


// Greedy algorithm
pair<vector<int>, set<int>> GreedySearch(const vector<vector<edge>>& graph, const vector<float>& query, const vector<vector<float>>& vectors, int start_node, int k, int L) ;
#endif // GREEDY_SEARCH_H 