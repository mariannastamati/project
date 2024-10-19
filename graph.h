#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <random>
#include <utility>
#include <algorithm>
#include <set>

using namespace std;


/*main idea: the final graph will be represented by an adjacency list where every neighbor has a pair with the node
and the distance (Euclidean distance). 

size: the number of nodes in graph
R: the number of random neighbors in every node
*/

// Create edge of graph (int: neighbor and float: distance)
using edge = pair<int, float>;

// Function to calculate Euclidean Distance
float EuclideanDistance(const vector<float>& node1, const vector<float>& node2);

// Creates a random R-regular directed graph
vector<vector<edge>> CreateGraph(const vector<vector<float>>& data, int size, int R);


#endif