#include "graph.h"


// Function to calculate Euclidean Distance
double EuclideanDistance(const vector<float>& node1, const vector<float>& node2){

    if (node1.size() != node2.size()) {
        throw invalid_argument("Vectors have different size.");
    }

    double sum = 0.0;
    int size = node1.size();
    for (int i = 0; i < size; ++i){

        double diff = (node1[i] - node2[i])*(node1[i] - node2[i]);
        sum = sum + diff;
    }
   
    double Euclidean = sqrt(sum);
    return Euclidean;
} 
