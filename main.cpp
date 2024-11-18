#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>

#include "io.h"
#include "print.h"
#include "cleandata.h"


int main(int argc, char **argv){

    // Check if given arguments are acceptable
    if (argc != 8) {
        cout << "Usage: <source_path> <query_path> <a> <t> <L> <R> <k>" << endl;
        return 1; // Exit with error
    }

    // Parse command-line arguments
    string source_path = argv[1];
    string query_path = argv[2];
    float a = atof(argv[3]);            // Threshold for RobustPrune algorithm (a>=1)
    int t = atoi(argv[4]);              // Threshold for FindMedoid algorithm
    int L = atoi(argv[5]);              // Search list size for GreedySearch algorithm
    int R = atoi(argv[6]);              // Number of max out-degree for every node
    int k = atoi(argv[7]);              // Number of nearest neighbors we want to find
    
    // Print arguments
    cout << "Prune threshold a: " << a << endl;
    cout << "Medoid threshold t: " << t << endl;
    cout << "Search list size L: " << L << endl;
    cout << "Max out-degree R: " << R << endl;
    cout << "Number of nearest neighbors k: " << k << endl << endl;
    

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

    return 0;
}