#include "FilteredVamana.h"


// Filtered Vamana Indexing algorithm
vector <graph> FilteredVamana(vector<vector<float>> &nodes, float a, int L, int R, int threshold, vector<Map> &STf){

    // Initialize G to an empty graph (just nodes, no neighbors no edges)
    vector<graph> G;

    // Add filters to every node and an empty neighbors list
    int size = nodes.size();
    for(int i = 0; i < size; i++){

        graph node;
        node.filter = nodes[i][0];
        node.neighbors = {};
        G.push_back(node);
    }

    // Remove filters from dataset to κeep only vectors (for euclidean distance calculation)
    vector<vector<float>> temp = nodes;
    RemoveFilters(temp);

    // Find start node (medoid of cluster) for every filter f
    STf = FindMedoid(nodes,threshold);

    // Sigma (σ) is a random permutation of points 1..n (n = the points in the dataset)
    vector<int> sigma = random_permutation(nodes);

    // For every node in dataset
    for(int i = 0; i < size; i++){

        // Find the start node of filter of σ[i]
        int currentPoint = sigma[i];
        float currentFilter = nodes[currentPoint][0];

        // Call Filtered Greedy Search
        auto [K_neighbors, visited_nodes] = FilteredGreedySearch(STf, temp[currentPoint], 0, L, temp, G, currentFilter);
        (void) K_neighbors;

        // Call Filtered Robust Pune to update out-neighbors of σ[i]
        G = FilteredRobustPrune(currentPoint, visited_nodes, a, R, G, nodes);

        // For every Neighbor j of sigma[i]
        vector<edge> nb = G[sigma[i]].neighbors;
        int Vsize = nb.size();
        for(int j = 0; j < Vsize; j++){

            int NearNeighbor = nb[j].first;
            vector<edge> &jneighbors = G[NearNeighbor].neighbors;
            int NNsize = jneighbors.size(); 

            // Checking if sigma[i] already exists in the Nearest Neighbor j
            bool exists = false;
            for(int k = 0; k < NNsize; k++){
                   
                if(jneighbors[k].first == sigma[i])
                {
                   exists = true;
                   break;
                }
            }

            // If it doesn't already exists add sigma[i] in the neighbors of NearNeighbor
            if(exists == false){

                float distance = EuclideanDistance(temp[NearNeighbor],temp[sigma[i]]);
                G[NearNeighbor].neighbors.emplace_back(sigma[i], distance);
            } 

            int nnsize = G[NearNeighbor].neighbors.size();
            if(nnsize > R){

                // Run Filtered Robust Prune to update out-neighbors of j
                vector<int> nb_nodes;
                for(int l = 0; l < nnsize; l++){

                    nb_nodes.emplace_back(jneighbors[l].first);
                }

                G = FilteredRobustPrune(j, nb_nodes, a, R, G, nodes);
            }
        }
    }

    // For every start node add some extra neighbors (chosen from other start nodes)
    int stf_size = STf.size();
    int R_stitched = static_cast<int>(round(stf_size * 0.05));
    for(int i = 0; i < stf_size; i++){

        // Choose R_stitched random start nodes (except it self)
        vector<int> randomNeighbors = choose_N_random_nodes(R_stitched, 0, stf_size-1, i);

        int node = STf[i].start_node;
        for (int j = 0; j < R_stitched; ++j){

            int selected_neighbor = STf[randomNeighbors[j]].start_node;

            float distance = 0.0;   // For Euclidean distance

            // Calculate euclidean distance between the i node and the neighbor
            distance = EuclideanDistance(nodes[node], nodes[selected_neighbor]);

            // Add neighbor and distance
            G[node].neighbors.emplace_back(selected_neighbor, distance);
        }
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