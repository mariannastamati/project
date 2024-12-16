#ifndef RECALL_H
#define RECALL_H


#include <iostream>
#include <vector>
#include <set>
#include <iomanip>

#include "graph.h"
#include "medoid.h"
#include "cleandata.h"
#include "FilteredGreedySearch.h"

using namespace std;

// Function to run Filtered Greedy and find recall for every query point
float Greedy_and_recall(vector<vector<float>> nodes, vector<vector<float>> queries, vector<vector<int>> gt,
    vector<graph> G, vector<Map> STf, int k, int L);

//Function to calculate the recall for a specific query
float Recall(vector<int> GreedyNeighbors, vector<int> TrueNeighbors, int k);

// Function to divide ints and return float result
float divide(int i, int b);

// Function to calculate and print the Overall recall
void OverallRecall(float sum, int queries_size); 

#endif