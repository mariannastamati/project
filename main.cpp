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

    int L = 50;
    int R = 4;          // Number of neighbors per node
    int medoid = -1;    // The medoid of graph

    // Vamana Indexing Algorithm (Creation of Vamana Graph)
    vector<vector<edge>> VamanaGraph = VamanaIndexing(vectors, L, R, medoid);
    
    PrintGraph(VamanaGraph);


    // παραδείγματα τιμών για τον Greedy
    //  int start_node = 8736;                 
    //  int k = 10;                                                       
    //vector<float> query = vectors[start_node];  // Query point

    // Εκτέλεση Greedy Search
    // auto [result_set, visited_nodes] = GreedySearch(VamanaGraph, query, vectors, start_node, k, L);


    // Εκτύπωση αποτελεσμάτων Greedy 
    //  cout << "K nearest nodes: ";
    // for (int node : result_set) {
    //     cout << node << " ";
    // }
    //  cout << endl;

    // Εκτύπωση των επισκεφθέντων κόμβων Greedy
    // cout << "Visited nodes: ";
    //  for (int node : visited_nodes) {
    //      cout << node << " ";
    //   }
    //    cout << endl;

    return 0;
}