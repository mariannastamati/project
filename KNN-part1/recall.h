#ifndef RECALL_H
#define RECALL_H


#include <iostream>
#include <vector>
#include <set>
#include <iomanip>

using namespace std;


//Function to calculate the recall for a specific query
float Recall(vector<int> GreedyNeighbors, vector<int> TrueNeighbors, int k);

// Function to divide ints and return float result
float divide(int i, int b);

// Function to calculate and print the Overall recall
void OverallRecall(float sum, int queries_size); 

#endif