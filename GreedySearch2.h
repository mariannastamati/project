#ifndef GREEDY_SEARCH_H
#define GREEDY_SEARCH_H

#include "graph.h"
#include <set>
#include <algorithm>


using namespace std; 


// Greedy algorithm
pair<vector<int>, set<int>> GreedySearch(int medoid, const vector<float>& query, int k, int L, const vector<vector<float>>& vectors,
const vector<vector<edge>>& graph) ;
#endif // GREEDY_SEARCH_H 