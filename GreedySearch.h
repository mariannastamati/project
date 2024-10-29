#ifndef GREEDY_SEARCH_H
#define GREEDY_SEARCH_H

#include "graph.h"
#include <set>
#include <algorithm>

using namespace std; 


// Greedy Search Algorithm 
pair<vector<int>, set<int>> GreedySearch(int medoid, const vector<float>& query, int k, int L,
    const vector<vector<float>>& vectors, const vector<vector<edge>>& graph);



// Greedy Search Marianna 1
pair<vector<int>, set<int>> GreedySearch(const vector<vector<edge>>& graph, const vector<float>& query, 
    const vector<vector<float>>& vectors, int start_node, int k, int L);

#endif // GREEDY_SEARCH_H 