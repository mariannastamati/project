#include "recall.h"


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
    cout << "Overall Recall: " << overall << "%" << endl;
}  