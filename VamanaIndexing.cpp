#include "VamanaIndexing.h"

// Creates a random R-regular directed graph
GraphNode* CreateGraph(const vector<vector<float>>& data, int size, int R){

    // Creating the Graph table
    GraphNode* GraphTable = new GraphNode[size];

    // Initializing Graph
    for (int i = 0; i < size; ++i){

        // Initializing node name
        GraphTable[i].node_name = const_cast<vector<float>*>(&data[i]);

        // Creating neighbors table for node i
        GraphTable[i].neighbors = new vector<float>*[R];

        // Generate R random numbers (R random neighbors)
        for (int j = 0; j < R; j++){

            // Random number generator
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distr(0, R-1);   // Choose a number between 0 to R-1

            // Generate random number 
            int randomNeighbor = distr(gen);

            // If random neighbor is not the same as the current node, add it to the neighbors table
            if (randomNeighbor != i){

                GraphTable[i].neighbors[j] = const_cast<vector<float>*>(&data[randomNeighbor]);
            }else{
                j--;       // Decrease j and try generate another random number
            }
        }
    }

    return GraphTable;
}



void VamanaIndexing(const vector<vector<float>>& data, int size, int R){ 

    // Create and initialize a random R-regular directed graph
    GraphNode* RandomGraph = CreateGraph(data, size, R);

}