#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <random>
#include <utility>
#include <algorithm>
#include <set>

using namespace std;


/* Graph main idea: the final graph will be represented by an adjacency list, where every neighbor is represented by a pair 
containing the node number and the distance (Euclidean distance). Also every node has only R out-degrees (neighbors) 
and only <= R in-degrees.

size: the number of nodes in graph
R: the number of random neighbors in every node
*/

// Create edge of graph (int: neighbor and float: distance)
using edge = pair<int, float>;

// Function to calculate Euclidean Distance
double EuclideanDistance(const vector<float>& node1, const vector<float>& node2);

// Creates a random R-regular directed graph
vector<vector<edge>> CreateGraph(const vector<vector<float>>& data, int size, int R);

// Function to find medoid of a Graph (Brute Force)
int Medoid(const vector<vector<float>>& data);


#endif