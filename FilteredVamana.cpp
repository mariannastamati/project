#include "FilteredVamana.h"


// Filtered Vamana Indexing algorithm
vector <graph> FilteredVamana(vector<vector<float>> &nodes, float a, int L, int R, int threshold){

    // Initialize G to an empty graph
    vector<graph> G;

    // Remove filters from dataset to κeep only vectors (for euclidean distance calculation)
    vector<vector<float>> temp = nodes;
    RemoveFilters(temp);

    // Find Medoid on dataset (we don't use it in this algorithm)
    //int s = Medoid(temp);

    // Find start node (medoid of cluster) for every filter f
    vector<Map> STf = FindMedoid(nodes,threshold);

    // Sigma (σ) is a random permutation of points 1..n (n = the points in the dataset)
    vector<int> sigma = random_permutation(nodes);

    // For every node in dataset
    int size = nodes.size();
    for(int i = 0; i < size; i++){

        // Find the start node of filter of σ[i]
        int currentPoint = sigma[i];
        float currentFilter = nodes[currentPoint][0];
        int startNode = findStartNodeFromFilter(STf, currentFilter);

        // Call Filtered Greedy Search
        //  auto [K_neighbors, visited_nodes] = FilteredGreedySearch(startNode, temp[currentPoint], 0, L, currentFilter, temp, G);
        // (void) K_neighbors;

        // Call Filtered Robust Pune to update out-neighbors of σ[i]
        // G = FilteredRobustPrune(currentPoint, visited_nodes, a, R);

        // For every Nearest Neighbor j of sigma[i]
        //vector<edge> nb = G[sigma[i]].neighbors;
        //Vsize = nb.size();
        //for(int j = 0; j < Vsize; j++){

        //    int NearNeighbor = nb[j];

        //    int NNsize = G[NearNeighbor].neighbors.size(); 

            // Checking if sigma[i] already exists in the Nearest Neighbor j
        //    bool exists = false;
        //    for(int k = 0; k < NNsize; k++){
                   
        //        if(nb[k].first == sigma[i])
        //        {
        //            exists = true;
        //            break;
        //        }

        //    }

            // If it doesn't already exists add sigma[i] in the neighbors of NearNeighbor
            //if(exists == false){

            //  float distance = EuclideanDistance(temp[NearNeighbor],temp[sigma[i]]);
            //  G[NearNeighbor].neighbors.emplace_back(sigma[i], distance);
            //} 

            //int nnsize = G[NearNeighbor].neighbors.size();
            //if(nnsize > R){

                    // Run Filtered Robust Prune to update out-neighbors of j
                    //vector<int> nb_nodes;
                    //for(int l = 0; l < Vsize; l++){

                        //nb_nodes.emplace_back(nb[l].first);
                    //}
                    // G = FilteredRobustPrune(j, nb_nodes, a, R);
            //}

        //}
    }

    return G;
}


// Function to create a random permutation of data
vector<int> random_permutation(const vector<vector<float>>& data){

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