#ifndef GREEDY_SEARCH_H
#define GREEDY_SEARCH_H

#include "graph.h"
#include <set>
#include <algorithm>


using namespace std; 


// Greedy algorithm
vector<int> GreedySearch(const vector<vector<edge>>& graph, int start_id, const vector<float>& query, int k, int L);

#endif // GREEDY_SEARCH_H 