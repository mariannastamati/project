#ifndef PRINTGRAPH_H
#define PRINTGRAPH_H

#include <iostream>
#include <vector>
#include "graph.h"  // Υποθέτουμε ότι το αρχείο "graph.h" έχει τον τύπο `edge`

void PrintGraph(const std::vector<std::vector<edge>>& graph);

// Function to count total edges in a graph
int CountTotalEdges(const std::vector<std::vector<edge>>& graph);

#endif
