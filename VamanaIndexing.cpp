#include "VamanaIndexing.h"


vector<vector<edge>> VamanaIndexing(const vector<vector<float>>& data, int size, int R){ 

    // Create and initialize a random R-regular directed graph
    vector<vector<edge>> Graph = CreateGraph(data, size, R);


    //------------------FIND MEDOID------------------
    // Variabes for the calculation of medoid
    int s = -1;                                 // Medoid variable (initialized with a fake medoid)
    float minsum = INFINITY;                    // Variable to help find min sum (initialized with a fake sum)
   
    // Keep only 5% of the nodes of the Graph as sample nodes
    int five_percent = static_cast<int>(Graph.size() * 0.05);

    // Random number generator
    random_device rd;
    mt19937 gen(rd());

    // Vector to keep the random sample nodes to check for medoid
    vector<int> sample_nodes(five_percent);

    // The range of numbers to choose from
    vector<int> Num_range(Graph.size());
    iota(Num_range.begin(), Num_range.end(), 0);
    sample(Num_range.begin(), Num_range.end(), sample_nodes.begin(), five_percent, gen);

    // Find Medoid (s) Algorithm
    Medoid(data, Graph, s, sample_nodes, minsum);

    cout << "Medoid is: " << s << endl;
    //-----------------------------------------------


    

    return Graph;
}