#include "printGraph.h"

void PrintGraph(const std::vector<std::vector<edge>>& graph) {
    for (int i = 0; i < graph.size(); ++i) {
        std::cout << "Node " << i << ": ";
        for (const auto& e : graph[i]) {
            std::cout << "(" << e.first << ", " << e.second << ") ";
        }
        std::cout << std::endl;
    }
}

// Function to count total edges in a graph
int CountTotalEdges(const std::vector<std::vector<edge>>& graph) {
    int total_edges = 0;
    for (const auto& node_neighbors : graph) {
        total_edges += node_neighbors.size();
    }
    return total_edges;
}