#include "recall.h"


// Function to run Filtered Greedy and find recall for every query point
float Greedy_and_recall(vector<vector<float>> nodes, vector<vector<float>> queries, vector<vector<int>> gt,
    vector<graph> G, vector<Map> STf, int k, int L){

    vector<vector<float>> q_filtered;       // To keep filtered queries
    vector<vector<float>> q_unfiltered;     // To keep unfiltered queries
    vector<int> gtf;                        // To keep groundtruth num for filtered
    vector<int> gtu;                        // To keep groundtruth num for unfiltered

    // For every query point in "Queries dataset" separate filtered queries from unfiltered queries  
    int queries_size = queries.size();
    for(int i = 0; i < queries_size; i++){

        // If query_type=0 we have unfiltered query, else filtered
        if(queries[i][0] == 0){
            q_unfiltered.push_back(queries[i]);
            gtu.push_back(i);

        }else{
            q_filtered.push_back(queries[i]);
            gtf.push_back(i);
        }
    }

    // Remove filters from dataset (to calculate Euclidean distance in Filtered Greedy - vector 100 dimensions)
    vector<vector<float>> tempnodes = nodes;
    RemoveFilters(tempnodes);

    // Remove query_type form queries dataset (vector with 101 dimensions)
    vector<vector<float>> f_tempqueries = q_filtered;
    RemoveFilters(f_tempqueries);
    vector<vector<float>> u_tempqueries = q_unfiltered;
    RemoveFilters(u_tempqueries);

    // Remove filters from queries dataset (to calculate Euclidean distance in Filtered Greedy - vector 100 dimensions)
    vector<vector<float>> fq_vector = f_tempqueries;
    RemoveFilters(fq_vector);
    vector<vector<float>> uq_vector = u_tempqueries;
    RemoveFilters(uq_vector);

    float sum_filtered = 0.0;
    float sum_unfiltered = 0.0;
    float sum = 0.0;

    // For every query in filtered queries
    int f_size = q_filtered.size();
    for(int i = 0; i < f_size; i++){

        vector<float> query = fq_vector[i];           // Query point
        float query_filter = f_tempqueries[i][0];     // Filter of query

        // Find k nearest neighbors for query using Filtered Greedy Search
        auto [neighbors_list, visited_nodes] = FilteredGreedySearch(STf,query,k,L,tempnodes,G,query_filter);


        // If query filter doesn't exist in dataset (move to next query)
        if (neighbors_list.empty()){

            sum_filtered = sum_filtered + 1.0;
            cout << "Moving to next query." << endl;
            continue;
        }

        // Calculate the recall (check for same neighbors between groundtruth vector and K-neighbors from Greedy)
        float recall = 0.0;
        int n_size = neighbors_list.size();

        // If nearest neighbors are less than k, set k to n_size (for filtered queries mostly)
        if(n_size < k){

            recall = Recall(neighbors_list, gt[gtf[i]], n_size);

        }else{
            recall = Recall(neighbors_list, gt[gtf[i]], k);
        }
        
        sum_filtered = sum_filtered + recall;
    }

    cout << "Filtered Queries ";
    OverallRecall(sum_filtered,f_size);
    cout << endl;


    // For every query in unfiltered queries  
    int u_size = q_unfiltered.size(); 
    for(int i = 0; i < u_size; i++){

        vector<float> query = uq_vector[i];          // Query point
        float query_filter = u_tempqueries[i][0];    // Filter of query

        // Find k nearest neighbors for query using Filtered Greedy Search
        auto [neighbors_list, visited_nodes] = FilteredGreedySearch(STf,query,k,L,tempnodes,G,query_filter);

        // Calculate the recall (check for same neighbors between groundtruth vector and K-neighbors from Greedy)
        float recall = 0.0;
        recall = Recall(neighbors_list, gt[gtu[i]], k);
        
        sum_unfiltered = sum_unfiltered + recall;
    }

    cout << "Unfiltered Queries ";
    OverallRecall(sum_unfiltered,u_size);

    sum = sum_filtered + sum_unfiltered;
    return sum;
}


//Function to calculate the recall for a specific query
float Recall(vector<int> GreedyNeighbors, vector<int> TrueNeighbors, int k){

    // Using a set to check for common elements
    set<int> commonElements;

    // Add GreedyNeighbors to set
    for (int GN : GreedyNeighbors){
        commonElements.insert(GN);
    }

    // Checking for common neighbors with TrueNeighbors
    int count = 0;
    for (int T : TrueNeighbors){

        if (commonElements.count(T)){
            count++;                    // Increase count if a neighbor is the same
        }
    }

    float recall = divide(count, k);
    return recall;
}


// Function to divide ints and return float result
float divide(int i, int b){
    return static_cast<float>(i) / static_cast<float>(b);
}


// Function to calculate and print the Overall recall
void OverallRecall(float sum, int queries_size){

    float overall = sum / static_cast<float>(queries_size);

    // Print Recall but keep only 2 decimal
    cout << fixed << setprecision(2);
    cout << "Overall Recall: " << overall*100 << "%" << endl;
} 