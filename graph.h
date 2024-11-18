#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/* Graph main idea: the final graph will be represented by a vector that contains a filter and a list of neighbors (for every node), 
where every neighbor is represented by a pair containing the node number and the distance (Euclidean distance).
Also every node has <= R out-degrees (neighbors).*/


// Create edge of graph (int: neighbor and float: distance)
using edge = pair<int, float>;

// Graph node structure
struct graph{

    float filter;               // Filter of node
    vector<edge> neighbors;     // Neighbors of node
};


// Function to calculate Euclidean Distance
double EuclideanDistance(const vector<float>& node1, const vector<float>& node2);


#endif