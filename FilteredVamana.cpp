#include "FilteredVamana.h"


// Filtered Vamana Indexing algorithm
vector <graph> FilteredVamana(vector<vector<float>> &nodes, float a, int L, int R, int threshold){

    // Initialize G to an empty graph
    vector<graph> G;

    // Remove filters from dataset to help find medoid of dataset
    vector<vector<float>> temp = nodes;
    RemoveFilters(temp);

    // Find Medoid on dataset
    int s = Medoid(temp);

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

        // the same as part 1
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