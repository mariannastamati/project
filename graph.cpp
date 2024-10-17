#include "graph.h"


// Function to calculate Euclidean Distance
float EuclideanDistance(const vector<float>& node1, const vector<float>& node2){

    float sum = 0.0;

    for (size_t i = 0; i < node1.size(); ++i) {
        sum = sum + pow(node2[i] - node1[i], 2);
    }
    
    return sqrt(sum);
} 



// Creates a random R-regular directed graph
vector<vector<edge>> CreateGraph(const vector<vector<float>>& data, int size, int R){

    // Create adjacency list
    vector<vector<edge>> Graph(size);

    // For every node of the graph connect R random neighbors
    for (size_t i = 0; i < size; ++i){
        for (size_t j = 0; j < R; ++j){

            float distance = 0.0;   // For Euclidean distance

            // Random number generator (for Rrandom neighbors of node i)
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distr(0, data.size() - 1);   // Choose a number between 0 to R-1

            // Generate random number 
            int randomNeighbor = distr(gen);

            // If random neighbor is not the same as the current node, add it to neighbors
            if (randomNeighbor != i){

                // Calculate euclidean distance between the i node and the neighbor
                distance = EuclideanDistance(data[i],data[randomNeighbor]);

                // Add neighbor and distance
                Graph[i].emplace_back(randomNeighbor, distance);

            }else{
                j--;       // Decrease j and try generate another random number
            }
        }
    }
    return Graph;
}
