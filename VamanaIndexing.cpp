#include "VamanaIndexing.h"
#include "graph.h"


void VamanaIndexing(const vector<vector<float>>& data, int size, int R){ 

    // Create and initialize a random R-regular directed graph
    vector<vector<edge>> RandomGraph = CreateGraph(data, size, R);

    // Print Random graph 
    for (int i = 0; i < RandomGraph.size(); ++i) {
        cout << "Node " << i + 1 << " -> ";
        for (const auto& edge : RandomGraph[i]) {
            std::cout << "(" << edge.first + 1 << ", " << edge.second << ") ";
        }
        cout << endl << endl;
    }

}