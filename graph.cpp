#include "graph.h"


// Function to calculate Euclidean Distance
double EuclideanDistance(const vector<float>& node1, const vector<float>& node2){

    if (node1.size() != node2.size()) {
        throw invalid_argument("Vectors have different size.");
    }

    double sum = 0.0;

    for (size_t i = 0; i < node1.size(); ++i){

        double diff = node2[i] - node1[i];
        sum = sum + (diff * diff);
    }
    
    double Euclidean = sqrt(sum);
    return Euclidean;
} 



// Creates a random R-regular directed graph
vector<vector<edge>> CreateGraph(const vector<vector<float>>& data, int size, int R){

    // Create adjacency list
    vector<vector<edge>> Graph(size);

    // Counter for in-degree number of every node
    vector<int> in_degree(size, 0);

    // For every node of the graph connect R random neighbors
    for (int i = 0; i < size; ++i){
        
        set<int> selectedNeighbors; // Create a set to keep selected neighbors (to check for duplicates)

        for (int j = 0; j < R; ++j){

            // Random number generator (for Rrandom neighbors of node i)
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distr(0, data.size() - 1);   // Choose a number between 0 to R-1
    
            // Generate random number 
            int randomNeighbor = distr(gen);

            // If random neighbor is not the same as the current node and different from other neighbors and has <= R in-degrees
            if (randomNeighbor != i && selectedNeighbors.count(randomNeighbor) == 0 && in_degree[randomNeighbor] <= R){

                selectedNeighbors.insert(randomNeighbor); // Add to selected neighbors

                float distance = 0.0;   // For Euclidean distance

                // Calculate euclidean distance between the i node and the neighbor
                distance = EuclideanDistance(data[i],data[randomNeighbor]);

                // Add neighbor and distance
                Graph[i].emplace_back(randomNeighbor, distance);
                
                // Increase the in-degree number of the choosen neighbor
                in_degree[randomNeighbor]++;

            }else{
                j--;       // Decrease j and try generate another random number
            }
        }
    }
    return Graph;
}



// Function to find the medoid of a Graph
int Medoid(const vector<vector<float>>& data){

    int medoid = -1;            // Variable to keep medoid
    double minsum = INFINITY;    // Variable to check for a smaller sum

    // Calculate the sum of Euclidean distance for every node of the graph with the other nodes
    int size = data.size();
    for (int i=0; i < size; i++){
        
        double sum = 0.0;

        for(int j=0; j < size; j++){
            if(i != j){   // If the nodes are not the same, calculate Euclidean distance
                
                sum = sum + EuclideanDistance(data[i],data[j]);
            }
        }

        // Check if a smaller sum is found and keep the new medoid of graph
        if(sum < minsum){

            minsum = sum;
            medoid = i;          // "i" node is the medoid
        }
    }
    cout << "Medoid of the Graph: " << medoid << endl;
    return medoid;
}