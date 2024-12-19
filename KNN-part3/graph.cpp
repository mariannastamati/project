#include "graph.h"


// Function to calculate Euclidean Distance
double EuclideanDistance(const vector<float>& node1, const vector<float>& node2){

    if (node1.size() != node2.size()) {
        throw invalid_argument("Vectors have different size.");
    }

    double sum = 0.0;
    int size = node1.size();
    for (int i = 0; i < size; ++i){

        double diff = (node1[i] - node2[i])*(node1[i] - node2[i]);
        sum = sum + diff;
    }
   
    double Euclidean = sqrt(sum);
    return Euclidean;
} 


vector<int> choose_N_random_nodes(int N, int start, int finish, int self){

    int i;
    vector<int> choosableNodes;

    for(i = start; i <= finish; i++)
    {
        if(i == self)
            continue;

        choosableNodes.push_back(i);
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(choosableNodes.begin(), choosableNodes.end(), gen);

    return vector<int>(choosableNodes.begin(), choosableNodes.begin() + N);
}


// Creates a random R-regular directed graph
vector<vector<edge>> CreateGraph(const vector<vector<float>>& data, int size, int R){

    // Create adjacency list
    vector<vector<edge>> Graph(size);

    // For every node of the graph connect R random neighbors
    for (int i = 0; i < size; ++i){

        vector<int> randomNeighbors = choose_N_random_nodes(R, 0, size-1, i);

        for (int j = 0; j < R; ++j){

            float distance = 0.0;   // For Euclidean distance

            // Calculate euclidean distance between the i node and the neighbor
            distance = EuclideanDistance(data[i], data[randomNeighbors[j]]);

            // Add neighbor and distance
            Graph[i].emplace_back(randomNeighbors[j], distance);
        }
    }

    return Graph;
}