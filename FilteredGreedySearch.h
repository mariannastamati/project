#ifndef FILTERED_GREEDY_SEARCH_H
#define FILTERED_GREEDY_SEARCH_H

#include <vector> 
#include <set>
#include "medoid.h"


using namespace std; 


//  Filtered Greedy Search Algorithm 
pair<vector<int>, vector<int>> FilteredGreedySearch( const vector<Map>& medoids,
   const vector<float>& query, 
    int k, 
    int L, 
    const vector<vector<float>>& vectors,
    const vector<vector<int>>& graph,
    const vector<fnode>& filters);

#endif // FILTERED_GREEDY_SEARCH_H