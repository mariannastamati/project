#include "graph.h"


// Function to calculate Euclidean Distance
float EuclideanDistance(const vector<float>& node1, const vector<float>& node2){

    float sum = 0.0;

    for (size_t i = 0; i < node1.size(); ++i) {
        sum = sum + pow(node2[i] - node1[i], 2);
    }
    
    float Euclidean = sqrt(sum);

    // Return Euclidean Distance but keep only one decimal
    return round(Euclidean * 10) / 10;
} 



// Creates a random R-regular directed graph
vector<vector<edge>> CreateGraph(const vector<vector<float>>& data, int size, int R){

    // Create adjacency list
    vector<vector<edge>> Graph(size);

    // For every node of the graph connect R random neighbors
    for (size_t i = 0; i < size; ++i){

        set<int> selectedNeighbors; // Create a set to keep selected neighbors (to check for duplicates)

        for (size_t j = 0; j < R; ++j){

            // Random number generator (for Rrandom neighbors of node i)
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distr(0, data.size() - 1);   // Choose a number between 0 to R-1
    
            // Generate random number 
            int randomNeighbor = distr(gen);

            // If random neighbor is not the same as the current node and different from other neighbors
            if (randomNeighbor != i && selectedNeighbors.count(randomNeighbor) == 0){

                selectedNeighbors.insert(randomNeighbor); // Add to selected neighbors

                float distance = 0.0;   // For Euclidean distance

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



// Function to find (the possible) medoid of a Graph
void Medoid(const vector<vector<float>>& data, vector<vector<edge>>& Graph, int& s, vector<int>& sample_nodes, float& minsum){
    
    int curMedoid = s;      // Vriable to check if the medoid has changed (means we found a better one)

    // Calculate the sum of Euclidean distance for every node of the sample nodes with the other nodes of the graph
    for (int i=0; i<sample_nodes.size(); i++){
        
        float sum = 0.0;

        for(int j=0; j< Graph.size(); j++){

            if(sample_nodes[i] != j){   // If the nodes are not the same, calculate Euclidean distance

                // If j belongs to the neighbors of sample_nodes[i], just add the distance to sum and continue to next
                bool flag = 0;
                for (const auto& edge : Graph[sample_nodes[i]]){
                    if (edge.first == j){

                        sum = sum + edge.second;
                        flag = 1;
                    }
                }

                // If j does not belong to the neighbors, calculate Euclidean distance and add it to sum
                if (flag == 0){
                    sum = sum + EuclideanDistance(data[sample_nodes[i]],data[j]);
                }
            }
        }

        // Check if a better medoid (s) is found
        if(sum < minsum){

            minsum = sum;
            s = sample_nodes[i];          // "sample_nodes[i]" node is the medoid (or better medoid)
            cout << "found better medoid " << s << endl;
        }
    }

    // If a new medoid is found, search if there is a better medoid in the neighbors of s
    if (s != curMedoid){

        // Add neighbors of s in a list and search for a "better" medoid
        vector<int> neighbors;
        for (const auto& edge : Graph[s]) {
            neighbors.push_back(edge.first); 
        }

        // Recursion to check for a new medoid
        Medoid(data, Graph, s, neighbors, minsum);
    }

    // No "better" medoid found, return
    return;
}