#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <random>
#include <utility>
#include <algorithm>
#include <set>

using namespace std;


/* Graph main idea: the final graph will be represented by an adjacency list where every neighbor has a pair with the node
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



/* Medoid main idea: To find the medoid of the Graph we just keep the 5% of the nodes of Graph as sample nodes and check
for a possible medoid in those nodes. When we find a possible medoid, we search in the neighbors of this possible medoid 
to check for a "better" possible medoid (if there is). If we find a "better" possible medoid we save it and continue
searching the new possible medoid's neighbors until we can't find a "better" medoid. That means we found the medoid of 
the Graph.

This algorithm checks for the medoid of a Graph using "Brute Force" method but only on the nodes it considers important. 
Τries "in a sample way" to find the correct result and reduce complexity of "Brute Force" method as much as possible.

NOTE: this algorithm works better in graphs with a lot of neighbors in every node.
*/

// Function to find medoid of a Graph
void Medoid(const vector<vector<float>>& data, vector<vector<edge>>& Graph, int& s, vector<int>& sample_nodes, float& minsum);


#endif