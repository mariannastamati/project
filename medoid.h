#ifndef MEDOID_H
#define MEDOID_H

#include <iostream>
#include <vector>
#include <algorithm> 
#include <random>
#include <iterator>
#include <climits>

#include "graph.h"

using namespace std;


// A struct to keep the filter type and a list with every node with the same filter type
struct fnode{

    float filter;
    vector<int> matching_points;
};

// A struct to help make a Map, mapping filters to start nodes
struct Map{

    float filter;
    int start_node;
};


// Function to find medoid (the start node) of every filter. Returns a map with filters and their start nodes
vector<Map> FindMedoid(vector<vector<float>> &nodes, int threshold);

// Function to choose τ random points from a vector
vector<int> randompoints(vector<int> &points, int t);

// Function to find the medoid of a dataset
int Medoid(const vector<vector<float>>& data);

#endif