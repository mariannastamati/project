#include <iostream>
#include "acutest.h"
#include "FilteredVamana.h"
#include "graph.h"
#include "FilteredRobustPrune.h"

using namespace std;


//---------- EUCLIDEAN DISTANCE FUNCTION ----------
/* Test 1 */
void EuclideanDistance_1(){
    
    // 2D Vectors
    vector<float> node1 = {1.5, 2.0};
    vector<float> node2 = {4.5, 6.0};

    double dist = EuclideanDistance(node1, node2);

    TEST_ASSERT(dist == 5.0);
}


/* Test 2 */
void EuclideanDistance_2(){
    
    // 5D Vectors
    vector<float> node1 = {15.0, 20.0, 35.0, 40.0, 25.0};
    vector<float> node2 = {45.0, 60.0, 5.0, 0.0, 50.0};

    double dist = EuclideanDistance(node1, node2);

    TEST_ASSERT(dist == 75.0);
}

//---------------- FILTERED ROBUST PRUNE FUNCTION ----------------
/* Test 1 - Test if the prune keeps max R nodes */
void FilteredRobustPrune_Test_1(){
    // Setup graph G with a few nodes and their neighbors
    vector<vector<float>> data = {
        {1.0, 1.0, 1.0},  // Node 0
        {1.0, 2.0, 2.0},  // Node 1
        {2.0, 3.0, 3.0},  // Node 2
        {2.0, 5.0, 5.0}   // Node 3
    };

    vector<graph> G(4); // 4 nodes in the graph

    // Add some neighbors to the nodes
    G[0].neighbors.push_back({1, 1.414});
    G[0].neighbors.push_back({2, 2.828});
    G[0].neighbors.push_back({3, 2.528});
    G[1].neighbors.push_back({0, 1.414});
    G[1].neighbors.push_back({3, 4.242});
    G[2].neighbors.push_back({0, 2.828});
    G[2].neighbors.push_back({1, 4.242});
    G[3].neighbors.push_back({1, 4.242});

    // Set filters for the nodes (just as an example)
    G[0].filter = 1.0;
    G[1].filter = 1.0;
    G[2].filter = 2.0;
    G[3].filter = 2.0;

    // Visited nodes list (currently empty)
    vector<int> visited_nodes;

    // Apply the prune
    G = FilteredRobustPrune(0, visited_nodes, 1.0, 1, G, data); // current node is 0, a = 1.0, R = 1

    // Check the number of neighbors for node 0
    TEST_ASSERT(G[0].neighbors.size() == 1); // Should be pruned to 1 neighbor
}

/* Test 2 - No Pruning */
void FilteredRobustPrune_Test_2(){
    // Setup graph with no neighbors for the current point
    vector<vector<float>> data = {
        {1.0, 1.0, 1.0},  // Node 0
        {1.0, 2.0, 2.0},  // Node 1
        {1.0, 3.0, 3.0}   // Node 2
    };

    vector<graph> G(3); // 3 nodes in the graph

    // No neighbors at all
    // G[0] has no neighbors, G[1] has no neighbors, G[2] has no neighbors

    // Set filters for the nodes
    G[0].filter = 1.0;
    G[1].filter = 1.0;
    G[2].filter = 1.0;

    // Visited nodes list (currently empty)
    vector<int> visited_nodes;

    // Apply the prune (shouldn't prune anything because there are no neighbors)
    G = FilteredRobustPrune(0, visited_nodes, 1.0, 2, G, data); // current node is 0, a = 1.0, R = 2

    // Ensure no changes happened (0 neighbors for node 0)
    TEST_ASSERT(G[0].neighbors.size() == 0); // No neighbors to prune
}

/* Test 3 - Pruning with Filter Difference */
void FilteredRobustPrune_Test_3(){
    // Setup graph with nodes having different filters
    vector<vector<float>> data = {
        {1.0, 1.0, 1.0},  // Node 0
        {1.0, 2.0, 2.0},  // Node 1
        {2.0, 3.0, 3.0},  // Node 2
        {2.0, 5.0, 5.0}   // Node 3
    };

    vector<graph> G(4); // 4 nodes in the graph

    // Add some neighbors to the nodes
    G[0].neighbors.push_back({1, 1.414});
    G[0].neighbors.push_back({2, 2.828});
    G[1].neighbors.push_back({0, 1.414});
    G[1].neighbors.push_back({3, 4.242});
    G[2].neighbors.push_back({0, 2.828});
    G[2].neighbors.push_back({1, 4.242});
    G[3].neighbors.push_back({1, 4.242});

    // Set filters for the nodes (different filters for node 0 and 3)
    G[0].filter = 1.0;
    G[1].filter = 1.0;
    G[2].filter = 2.0;
    G[3].filter = 2.0;

    // Visited nodes list (currently empty)
    vector<int> visited_nodes;

    // Apply the prune
    G = FilteredRobustPrune(0, visited_nodes, 1.0, 2, G, data); // current node is 0, a = 1.0, R = 2

    // Node 0 should not be connected to node 2 because of filter mismatch
    bool found_invalid_neighbor = false;
    for (const auto& neighbor : G[0].neighbors) {
        if (neighbor.first == 2) {
            found_invalid_neighbor = true;
            break;
        }
    }

    TEST_ASSERT(!found_invalid_neighbor); // Node 0 should not have node 2 as a neighbor
}

/* Test 4 - Edge Distance Check */
void FilteredRobustPrune_Test_4(){
    // Setup graph with nodes and distances
    vector<vector<float>> data = {
        {1.0, 0.0, 0.0},  // Node 0
        {1.0, 100.0, 100.0},  // Node 1
        {1.0, 1.0, 1.0}, // Node 2
        {1.0, 1000.0, 1000.0} // Node 3 
    };

    vector<graph> G(4); // 4 nodes in the graph

    // Add neighbors with distances
    G[0].neighbors.push_back({1, 1.0});
    G[0].neighbors.push_back({2, 1.0});
    G[0].neighbors.push_back({3, 1.0});

    // Set filters
    G[0].filter = 1.0;
    G[1].filter = 1.0;
    G[2].filter = 1.0;
    G[3].filter = 1.0;

    // Visited nodes list (currently empty)
    vector<int> visited_nodes;

    // Apply the prune
    G = FilteredRobustPrune(0, visited_nodes, 1.0, 5, G, data); // current node is 0, a = 1.0, R = 5

    // Ensure correct neighbors after pruning
    TEST_ASSERT(G[0].neighbors.size() == 1); // Should prune to 1 neighbor, delete node 1 and 3 as neighbors because distance greater than 1.0
}


/* Test Main */
TEST_LIST = {

    // Euclidean Distance Tests
    {"Euclidean Distance 1", EuclideanDistance_1},
    {"Euclidean Distance 2", EuclideanDistance_2},

    // Filtered Robust Prune Tests
    {"Filtered Robust Prune Test 1", FilteredRobustPrune_Test_1},
    {"Filtered Robust Prune Test 2", FilteredRobustPrune_Test_2},
    {"Filtered Robust Prune Test 3", FilteredRobustPrune_Test_3},
    {"Filtered Robust Prune Test 4", FilteredRobustPrune_Test_4},

    {NULL, NULL}
};