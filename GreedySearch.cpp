#include "GreedySearch.h"
#include "graph.h"
#include <queue>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

// function to compare two nodes (a, b) and select the closest one 
bool compare(int a, int b, const vector<float>& query, const vector<vector<float>>& vectors) {
    return EuclideanDistance(query, vectors[a]) > EuclideanDistance(query, vectors[b]);
}

// Greedy Search 
vector<int> GreedySearch(const vector<vector<edge>>& graph, const vector<float>& query, const vector<vector<float>>& vectors, int start_node, int k, int L){


    set<int> visited;                 // set for the nodes we have visited
    vector<int> result_set;           // result set 
    vector<int> search_list = {start_node};   // search list which we initialize with the start node 
    
    visited.insert(start_node);       







}
