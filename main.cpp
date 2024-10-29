#include <iostream>
#include <vector>
#include <iomanip>

#include "readfiles.h"
#include "printGraph.h"
#include "VamanaIndexing.h"
#include "GreedySearch.h"

#include <cstdlib>

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

    int k = 10;         // Number of nearest neighbors to find
    int L = 50;
    int R = 20;         // Number of neighbors per node
    int medoid = -1;    // The medoid of graph

    // Vamana Indexing Algorithm (Creation of Vamana Graph)
    vector<vector<edge>> VamanaGraph = VamanaIndexing(vectors, L, R, medoid);
    
    PrintGraph(VamanaGraph);


    // Greedy Search for every query point of the "Query Dataset"          
    int queries_size = queries.size(); 
    for(int i = 0; i < queries_size; i++){

        vector<float> query = queries[i];     // Query point

        //auto [result_set, visited_nodes] = GreedySearch(medoid, query, k, L, vectors, VamanaGraph);


        // Εκτύπωση αποτελεσμάτων Greedy 
        // cout << "K nearest nodes: ";
        // for (int node : result_set) {
        //     cout << node << " ";
        // }
        // cout << endl;

        // Εκτύπωση των επισκεφθέντων κόμβων Greedy
        // cout << "Visited nodes: ";
        // for (int node : visited_nodes) {
        //     cout << node << " ";
        // }
        // cout << endl;
    }                                                     
    

    return 0;
}