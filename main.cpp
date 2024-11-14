#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>

#include "io.h"
#include "print.h"


int main(int argc, char **argv){

    string source_path = "../datasets2/dummy-data.bin";
    string query_path = "../datasets2/dummy-queries.bin";
  

    // Also accept other path for source data
    if (argc > 1) {
        source_path = string(argv[1]);
    }

    uint32_t num_data_dimensions = 102;

    // Read data points
    vector <vector<float>> nodes;
    cout << "Reading data points..."<< endl;
    ReadBin(source_path, num_data_dimensions, nodes);
    cout<<"Num of nodes: " << nodes.size() << endl << endl;

    // Read queries
    uint32_t num_query_dimensions = num_data_dimensions + 2;
    vector <vector<float>> queries;
    cout << "Reading queries..."<< endl;
    ReadBin(query_path, num_query_dimensions, queries);

 
    return 0;
}