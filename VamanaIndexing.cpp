#include "VamanaIndexing.h"


vector<vector<edge>> VamanaIndexing(const vector<vector<float>>& data, int size, int R){ 

    // Create and initialize a random R-regular directed graph
    vector<vector<edge>> Graph = CreateGraph(data, size, R);

    // Find Medoid on Graph
    int s = Medoid(data, Graph);


    return Graph;
}