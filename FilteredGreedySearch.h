#ifndef FILTERED_GREEDY_SEARCH_H
#define FILTERED_GREEDY_SEARCH_H

#include <vector> 
#include <set>
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>

#include "graph.h"
#include "medoid.h"


using namespace std; 

inline vector<int> removeCommonElements(const vector<int>& visited, const vector<int>& neighbors_list);


//  Filtered Greedy Search Algorithm 
pair<vector<int>, vector<int>> FilteredGreedySearch( const vector<Map>& medoids, const vector<float>& query, 
    int k, 
    int L, 
    const vector<vector<float>>& vectors,
    const vector<graph>& graph,
    const float filter);

#endif // FILTERED_GREEDY_SEARCH_H
