#include "VamanaIndexing.h"


vector<vector<edge>> VamanaIndexing(const vector<vector<float>>& data, int size, int R){ 

    // Create and initialize a random R-regular directed graph
    vector<vector<edge>> Graph = CreateGraph(data, size, R);

    // Find Medoid on Graph
    //int s = Medoid(data, Graph);

    // Sigma (σ) is a random permutation of points 1..n (data size = n = the points in the dataset)
    vector<int> sigma = random_permutation(data);


    return Graph;
}



// Function to create a random permutation of data
vector<int> random_permutation(const vector<vector<float>>& data){

    vector<int> s(data.size());

    for(int i = 0; i <= data.size(); ++i){
        s[i] = i;
    }

    random_device rd;
    mt19937 gen(rd());

    // Suffle vector
    shuffle(s.begin(), s.end(), gen);

    return s;
}