#include "mainTools.h"


// Generate groundtruth Phase
void GenerateGroundtruthPhase(const string& source_path, const string& query_path, 
    uint32_t num_data_dimensions, uint32_t num_query_dimensions){

    vector<vector<float>> nodes;
    vector<vector<float>> queries;

    cout << "Reading data points..." << endl;
    ReadBin(source_path, num_data_dimensions, nodes);
    cout << endl;

    cout << "Reading queries..." << endl;
    ReadBin(query_path, num_query_dimensions, queries);
    cout << endl;

    // CLEAN DATA: Remove Timestamps from data
    CleanData(nodes);

    // CLEAN QUERIES: Revome query_type 2 and 3, and elements related to timestamps 
    CleanQueries(queries);

    cout << "Generating groundtruth file..." << endl;
    auto start = high_resolution_clock::now();
    generateGroundTruth(queries, nodes, 100);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();

    cout << "Groundtruth file created in " << duration << " ms" << endl;
}


// Filtered Vamana Phase
void FilteredVamanaPhase(const string& source_path, float a,int L, int R, uint32_t num_data_dimensions){

    // Print arguments
    cout << "Prune threshold a: " << a << endl;
    cout << "Search list size L: " << L << endl;
    cout << "Max out-degree R: " << R << endl << endl;

    vector<vector<float>> nodes;

    cout << "Reading data points..." << endl;
    ReadBin(source_path, num_data_dimensions, nodes);
    cout << endl;

    // CLEAN DATA: Remove Timestamps from data
    CleanData(nodes);

    // Medoid map
    vector<Map> STf;

    cout << "Running Filtered Vamana..." << endl;
    auto start = high_resolution_clock::now();
    vector<graph> G_Filtered = FilteredVamana(nodes, a, L, R, STf);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << "Filtered Vamana Graph created in " << duration << " ms" << endl;

    // Save graph to file.bin
    saveGraphToFile(G_Filtered, "G_filtered.bin");
}


// Stitched Vamana Phase
void StitchedVamanaPhase(const string& source_path, float a, int L_small, int R_small, int R_stitched, 
    uint32_t num_data_dimensions){

    // Print arguments
    cout << "Prune threshold a: " << a << endl;
    cout << "Search list size L_small: " << L_small << endl;
    cout << "Max out-degree R_small: " << R_small << endl;
    cout << "Max reduced out-degree R_stitched: " << R_stitched << endl << endl;

    vector<vector<float>> nodes;

    cout << "Reading data points..." << endl;
    ReadBin(source_path, num_data_dimensions, nodes);
    cout << endl;

    // CLEAN DATA: Remove Timestamps from data
    CleanData(nodes);

    // Find start node (medoid of cluster) for every filter f
    vector<Map> STf = FindMedoid(nodes);

    cout << "Running Stitched Vamana..." << endl;
    auto start = high_resolution_clock::now();

    // Keep 5% of start nodes to add as neighbors in Stitched Vamana
    int stf_size = STf.size();
    R_stitched = static_cast<int>(round(stf_size * 0.05));
    
    // This only helps if we have few filters (filters < 20)
    if((R_stitched > 0) && (R_stitched < 1)){
        R_stitched = 1;
    } 

    vector<graph> G_Stitched = StitchedVamana(nodes, a, L_small, R_small, R_stitched, STf);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << "Stitched Vamana Graph created in " << duration << " ms" << endl;

    // Save graph to file.bin
    saveGraphToFile(G_Stitched, "G_stitched.bin");
}


// Greedy Search and Recall Phase
void GreedySearchPhase(const string& source_path, const string& query_path, const string& groundtruth_path, 
    int L, int k, uint32_t num_data_dimensions, uint32_t num_query_dimensions, const string& filename){

    // Print arguments
    cout << "Search list size L: " << L << endl;
    cout << "Number of nearest neighbors k: " << k << endl << endl;

    vector<vector<float>> nodes;
    vector<vector<float>> queries;

    cout << "Reading data points..." << endl;
    ReadBin(source_path, num_data_dimensions, nodes);

    // CLEAN DATA: Remove Timestamps from data
    CleanData(nodes);
    cout<<"Num of data points (nodes): " << nodes.size() << endl << endl;


    cout << "Reading queries..." << endl;
    ReadBin(query_path, num_query_dimensions, queries);

    // CLEAN QUERIES: Revome query_type 2 and 3, and elements related to timestamps 
    CleanQueries(queries);
    cout << "Num of queries: " << queries.size() << endl << endl;


    cout << "Reading groundtruth..." << endl;
    vector<vector<int>> gt = readGroundtruth(groundtruth_path);
    cout << endl;

    // Read graph index
    vector<graph> Graph = ReadGraphFile(filename);

    // Find start node (medoid of cluster) for every filter f
    vector<Map> STf = FindMedoid(nodes); 

    cout << "Find k nearest neighbors for queries (using Greedy Search)..." << endl;
    float sum = Greedy_and_recall(nodes, queries, gt, Graph, STf, k, L);

    OverallRecall(sum, queries.size());
}