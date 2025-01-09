#include "VamanaIndexing.h"


vector<vector<edge>> VamanaIndexing(const vector<vector<float>>& data, float a, int L, int R, int& s){ 

    // Create and initialize a random R-regular directed graph
    vector<vector<edge>> Graph = CreateGraph(data, data.size(), R);

    // Sigma (σ) is a random permutation of points 1..n (data size = n = the points in the dataset)
    vector<int> sigma = random_permutation1(data);

    int size = data.size();
    for(int i = 0; i < size; i++){
        
        // Call Greedy Search giving arguments: x_0σ(i), s = medoid, k = 1 and L
        auto [K_neighbors, visited_nodes] = GreedySearch(s, data[sigma[i]], 1, L, data, Graph);
        
        // Call Robust Prune to update out-neighbors of σ[i] (sigma[i])
        vector<int> V = visited_nodes;       // Visited nodes of sigma[i] from Greedy Search

        Graph = RobustPrune(sigma[i], V, a, R, Graph, data);

        // For every Neighbor j of sigma[i]
        vector<edge> nb = Graph[sigma[i]];
        int Vsize = nb.size();
        for(int j = 0; j < Vsize; j++){

            int NearNeighbor = nb[j].first;

            int NNsize = Graph[NearNeighbor].size();

            // Checking if sigma[i] already exists in the Nearest Neighbor j
            bool exists = false;
            for(int k = 0; k < NNsize; k++)
            {
                if(Graph[NearNeighbor][k].first == sigma[i])
                {
                    exists = true;
                    break;
                }
            }

            // If exists set "extra" to 0
            int extra = (exists == true) ? 0 : 1;

            // If the number of Nearest Neighbors j with sigma[i] (an extra neighbor) is greater that R
            if ( NNsize + extra > R){

                // Create a vector with all the neighbors of the NearNeighbor (V[j])
                vector<int> neighbors(Graph[NearNeighbor].size());
                for (const edge& e : Graph[NearNeighbor]){
                    neighbors.push_back(e.first);
                }
                
                // Add sigma[i] to the neighbors
                if(exists == false){
                    neighbors.push_back(sigma[i]);
                }
            
                {
                    // Call Robust Prune to update out-neighbors of NearNeighbor (V[j])
                    Graph = RobustPrune(NearNeighbor, neighbors, a, R, Graph, data);
                }

            }else{
                // Else (if it doesn't already exists) add sigma[i] in the neighbors of NearNeighbor (V[j]) without pruning
                if(exists == false){

                    float distance = EuclideanDistance(data[NearNeighbor],data[sigma[i]]);
                    {
                        Graph[NearNeighbor].emplace_back(sigma[i], distance);
                    }
                } 
            }
        }
    }
    return Graph;
}



// Function to create a random permutation of data
vector<int> random_permutation1(const vector<vector<float>>& data){

    vector<int> s(data.size());

    int size = data.size();
    for(int i = 0; i < size; ++i){
        s[i] = i;
    }

    random_device rd;
    mt19937 gen(rd());

    // Suffle vector
    shuffle(s.begin(), s.end(), gen);

    return s;
}