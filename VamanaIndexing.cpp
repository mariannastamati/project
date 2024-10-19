#include "VamanaIndexing.h"


vector<vector<edge>> VamanaIndexing(const vector<vector<float>>& data, int size, int R){ 

    // Create and initialize a random R-regular directed graph
    vector<vector<edge>> Graph = CreateGraph(data, size, R);

    // Print Random graph 
    for (int i = 0; i < Graph.size(); ++i) {
        cout << "Node " << i + 1 << " -> ";
        for (const auto& edge : Graph[i]) {
            std::cout << "(" << edge.first + 1 << ", " << edge.second << ") ";
        }
        cout << endl << endl;
    }

    return Graph;
}