#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <chrono>

#include "io.h"
#include "print.h"
#include "cleandata.h"
#include "groundtruth.h"
#include "FilteredVamana.h"
#include "StitchedVamana.h"
#include "recall.h"

using namespace std::chrono;


int main(int argc, char **argv){

    // Check if given arguments are acceptable
    if (argc != 12) {
        cout << "Usage: <source_path> <query_path> <a> <t> <L> <R> <k> <L_smal> <R_small> <R_stitched>" << endl;
        return 1; // Exit with error
    }

    // Start time for whole program
    auto total_start = high_resolution_clock::now();


    // Parse command-line arguments
    string source_path = argv[1];
    string query_path = argv[2];
    float a = atof(argv[3]);            // Threshold for RobustPrune algorithm (a>=1)
    int t = atoi(argv[4]);              // Threshold for FindMedoid algorithm
    int L = atoi(argv[5]);              // Search list size for GreedySearch algorithm
    int R = atoi(argv[6]);              // Number of max out-degree for every node
    int k = atoi(argv[7]);              // Number of nearest neighbors we want to find

    int L_small = atoi(argv[8]);        // Search list size L for Stitched Vamana
    int R_small = atoi(argv[9]);        // Number of max out-degree for every node in Stitched Vamana
    int R_stitched = atoi(argv[10]);    // Number to reduce max out-degree for every node in Stitched Vamana
    string groundtruth = argv[11];      // Groundtruth file
    
    // Print arguments
    cout << "Prune threshold a: " << a << endl;
    cout << "Medoid threshold t: " << t << endl;
    cout << "Search list size L: " << L << endl;
    cout << "Max out-degree R: " << R << endl;
    cout << "Number of nearest neighbors k: " << k << endl << endl;

    cout << "- Arguments for Stitched Vamana only -" << endl;
    cout << "Search list size L_small: " << L_small << endl;
    cout << "Max out-degree R_small: " << R_small << endl;
    cout << "Max reduced out-degree R_stitched: " << R_stitched << endl << endl;


    uint32_t num_data_dimensions = 102;

    // Read data points
    vector<vector<float>> nodes;
    cout << "Reading data points..."<< endl;
    ReadBin(source_path, num_data_dimensions, nodes);
    cout<<"Num of nodes: " << nodes.size() << endl << endl;

    // Read queries
    uint32_t num_query_dimensions = num_data_dimensions + 2;
    vector<vector<float>> queries;
    cout << "Reading queries..."<< endl;
    ReadBin(query_path, num_query_dimensions, queries);

    // CLEAN DATA: Remove Timestamps from data
    CleanData(nodes);

    // CLEAN QUERIES: Revome query_type 2 and 3, and elements related to timestamps 
    CleanQueries(queries);
    cout << "Num of queries: " << queries.size() << endl << endl;

    // Generate groundtruth file for queries (for 100 nearest neighbors)
    //generateGroundTruth(queries,nodes,100);
    cout << "Reading groundtruth..."<< endl;
    vector<vector<int>> gt = readGroundtruth(groundtruth);        // Read Groundtruth

    // Vector to keep the start node for every filter
    vector<Map> STf;


    // Call Filtered Vamana algorithm to create a graph
    cout << endl << "Running Filtered Vamana..." << endl;
    // Start time for Filtered Vamana
    auto filtered_start = high_resolution_clock::now();
    vector <graph> G_Filtered = FilteredVamana(nodes,a,L,R,t,STf);
    // End time for Filtered Vamana
    auto filtered_end = high_resolution_clock::now();
    auto filtered_duration = duration_cast<milliseconds>(filtered_end - filtered_start).count();
    cout << "Complete. Filtered Vamana Graph created in " << filtered_duration << " ms" << endl << endl;


    // Call Stitched Vamana algorithm to create a graph
    cout << "Running Stitched Vamana..." << endl;
    // Start time for Stitched Vamana
    auto stitched_start = high_resolution_clock::now();
    vector <graph> G_Stitched = StitchedVamana(nodes,a,L_small,R_small,R_stitched,STf);
    // End time for Stitched Vamana
    auto stitched_end = high_resolution_clock::now();
    auto stitched_duration = duration_cast<milliseconds>(stitched_end - stitched_start).count();
    cout << "Complete. Stitched Vamana Graph created in " << stitched_duration << " ms" << endl << endl;


    // Filtered Greedy Search and recall for every query point in "Query Dataset"
    cout << "Find k nearest neighbors for queries (using Filtered Vamana Graph)..." << endl << endl;;
    float sum1 = Greedy_and_recall(nodes,queries,gt,G_Filtered,STf,k,L);
    
    // Print Overall Recall
    int queries_size = queries.size();
    OverallRecall(sum1, queries_size);
    cout << endl;

    // Filtered Greedy Search and recall for every query point in "Query Dataset"
    cout << "Find k nearest neighbors for queries (using Stitched Vamana Graph)..." << endl;
    float sum2 = Greedy_and_recall(nodes,queries,gt,G_Stitched,STf,k,L);
    
    // Print Overall Recall
    OverallRecall(sum2, queries_size);


    // Stop time for whole program
    cout << endl;
    auto total_end = high_resolution_clock::now();
    auto total_duration = duration_cast<milliseconds>(total_end - total_start).count();
    cout << "Total execution time: " << total_duration << " ms" << endl;

    cout << "-----------------------" << endl; 
    
    return 0;
}