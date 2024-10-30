#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>

#include "readfiles.h"
#include "printGraph.h"
#include "VamanaIndexing.h"
#include "recall.h"


int main(){

    // Reading input files
    string base_data = "../datasets/siftsmall/siftsmall_base.fvecs";
    vector<vector<float>> vectors = read_fvecs(base_data);

    // Reading query files
    string query_data = "../datasets/siftsmall/siftsmall_query.fvecs";
    vector<vector<float>> queries = read_fvecs(query_data);

    // Reading groundtruth files
    string groundtruth_data = "../datasets/siftsmall/siftsmall_groundtruth.ivecs";
    vector<vector<int>> groundtruth = read_ivecs(groundtruth_data);


    int k = 50;          // Number of nearest neighbors to find
    int L = 100;
    int R = 20;          // Number of neighbors per node
    int medoid = -1;     // The medoid of graph


    // Vamana Indexing Algorithm (Creation of Vamana Graph)
    vector<vector<edge>> VamanaGraph = VamanaIndexing(vectors, L, R, medoid);
    

    // Greedy Search for every query point of the "Query Dataset"   
    float sum = 0.0;     
    int queries_size = queries.size(); 
    for(int i = 0; i < queries_size; i++){

        vector<float> query = queries[i];     // Query point

        // Find k nearest neighbors for query
        auto [neighbors_list, visited_nodes] = GreedySearch(medoid, query, k, L, vectors, VamanaGraph);

        // Calculate the recall (check for same neighbors between groundtruth vector and K-neighbors from Greedy)
        float recall = Recall(neighbors_list, groundtruth[i], k);

        sum = sum + recall;

        // Print query Recall but keep only 2 decimal
        cout << fixed << setprecision(2);
        cout << "Recall: " << recall << "%" << endl;
    }

    // Print Overall Recall
    OverallRecall(sum, queries_size);                               
    
    return 0;
}