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








