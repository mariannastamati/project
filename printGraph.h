#ifndef PRINTGRAPH_H
#define PRINTGRAPH_H

#include "graph.h"  // Assume that "graph.h" contains the `edge` type

void PrintGraph(const std::vector<std::vector<edge>>& graph);

// Function to count total edges in a graph
int CountTotalEdges(const std::vector<std::vector<edge>>& graph);

#endif
