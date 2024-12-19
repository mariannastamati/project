#include <iostream>
#include "acutest.h"
#include "FilteredVamana.h"
#include "StitchedVamana.h"
#include "FilteredRobustPrune.h"
#include "FilteredGreedySearch.h"
#include "graph.h"

using namespace std;


void print(vector<int>& L, vector<int>& V)
{
    // Print knn
    cout << "K nearest nodes: ";
    for (int node : L) {
        cout << node << " ";
    }
    cout << endl;

    // Print Visited nodes
    cout << "Visited nodes: ";
    for (int node : V) {
        cout << node << " ";
    }
    cout << endl;
}


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


//------------ CREATE R-DIRECTED GRAPH ------------
void CreateGraph_1(){
    
    vector<vector<float>> points = {
        {1.0, 2.0},
        {2.0, 1.0},
        {0.0, 2.0},
        {0.0, 1.0},
        {4.0, 6.0},
        {0.0, 5.0},
        {3.0, 7.0}
    };

    int size = points.size();
    int R = 4;

    vector<vector<edge>> G = CreateGraph(points, size, R);

    bool flag = 0;
    int Gsize = G.size();
    for(int i = 0; i < Gsize; i++){

        int Neighbor_size = G[i].size();
        if(Neighbor_size != R){
            flag = 1;           // Set flag=1 if number of neighbors is not R
        }
    }

    // The graph must have N=points.size() nodes and every node must have R neighbors
    TEST_ASSERT((G.size() == points.size()) && (flag == 0));
}


//------------ GREEDY SEARCH ALGORITHM ------------
/* Test 1 */
void GreedySearch_1(){

    vector<vector<float>> points = {
        {1.0, 2.0},
        {2.0, 1.0},
        {0.0, 2.0},
        {1.0, 1.0},
        {1.0, 0.0}
    };

    int medoid = 3;
    vector<vector<edge>> G = CreateGraph(points, points.size(), 3);
    vector<float> q = {0.0, 2.0};       // Using query point that exists in the points of vector
    int k = 2;
    int L = 3;

   auto [K_neighbors, visited_nodes] = GreedySearch(medoid, q, k, L, points, G);

    cout << "\nGreedy search result:" << endl;
    print(K_neighbors, visited_nodes);

    // The first nearest neighbor to q must be himself (points[2])
    TEST_ASSERT(K_neighbors.size() == (long unsigned int) k);
}


/* Test 2 */
void GreedySearch_2(){

    vector<vector<float>> points = {
        {1.0, 2.0},
        {2.0, 1.0},
        {0.0, 2.0},
        {1.0, 1.0},
        {1.0, 0.0}
    };

    int medoid = 3;
    vector<vector<edge>> G = CreateGraph(points, points.size(), 3);
    vector<float> q = {0.0, 0.0};       // Using query point different from the points of vector
    int k = 2;
    int L = 3;

   auto [K_neighbors, visited_nodes] = GreedySearch(medoid, q, k, L, points, G);

    cout << "\nGreedy search result:" << endl;
    print(K_neighbors, visited_nodes);

    // 2 nearest neighbors to q must be points[3] and points[4]
    TEST_ASSERT(K_neighbors.size() == (long unsigned int) k);
}


// ------------ ROBUST PRUNE ALGORITHM ------------
void RobustPrune_1() {

    vector<vector<float>> points = {
        {1.0, 2.0},
        {2.0, 1.0},
        {0.0, 2.0},
        {1.0, 1.0},
        {1.0, 0.0},
        {1000.0, 1000.0},   // Outlier (Point 5)
        {500.0, 500.0}      // Another outlier (Point 6)
    };
    
    int medoid = 3;                 // Use point {1.0, 1.0} as medoid
    int R = 6;                      // Max out-neighbors
    float a = 1.0;                  // Pruning threshold
    vector<float> q = {2.0, 2.0};   // Query point
    int k = 4;
    int L = 9;

    vector<vector<edge>> G = CreateGraph(points, points.size(), R); // Create a graph with R neighbors

    // Run the Greedy Search to get the visited nodes set
    auto [K_neighbors, visited_nodes] = GreedySearch(medoid, q, k, L, points, G);

    // TEST TO PRUNE MEDOID NODE, points[3]
    vector<int> V = visited_nodes;
    // Now use the output of the greedy search as input to the prune function
    G = RobustPrune(medoid, V, a, R, G, points); // Perform Robust Prune

    // Assertions to check the expected outcomes
    TEST_ASSERT(G[medoid].size() < static_cast<size_t>(R)); // Check that the number of neighbors is less than R

    for (const edge& e : G[medoid]) {
        int neighbor = e.first;
        TEST_ASSERT(neighbor != 5 && neighbor != 6); // Ensure no outliers are included as neighbors
    }
}


// ------------ CLEAN DATA FUNCTION ------------
void CleanData_1(){

    vector<vector<float>> points = {
        {1.0, 1.3, 3.0}
    };

    cout << endl << "Vector size with timestamp: " << points[0].size() << endl;

    // Remove second element (timestamp)
    CleanData(points);

    cout << "Vector size without timestamp: " << points[0].size() << endl;

    // Size of vector must be 2 
    TEST_ASSERT(points[0].size() == (long unsigned int) 2);
}


// ------------ CLEAN QUERIES FUNCTION ------------
void CleanQueries_1(){

    // Query type is the first element in vectors
    vector<vector<float>> points = {
        {1.0, 1.3, 3.0, 4.0, 5.0, 6.0, 7.0},
        {2.0, 1.3, 3.0, 4.0, 5.0, 6.0, 7.0},
        {0.0, 1.3, 3.0, 4.0, 5.0, 6.0, 7.0},
        {1.0, 1.3, 3.0, 4.0, 5.0, 6.0, 7.0},
        {3.0, 1.3, 3.0, 4.0, 5.0, 6.0, 7.0}
    };

    cout << endl << "Vector size with timestamp queries: " << points.size() << endl;
    cout << "Vectors of vector size with timestamp elements: " << points[0].size() << endl;

    // Remove query type 2 and 3 and elements related to timestamps
    CleanQueries(points);

    cout << "Vector size without timestamp queries: " << points.size() << endl;
    cout << "Vectors of vector size without timestamp elements: " << points[0].size() << endl;

    // Size of vector must be 3 and every vector must have size = 5
    TEST_ASSERT((points.size() == (long unsigned int) 3) && (points[0].size() == (long unsigned int) 5));     
}


// ------------ REMOVE FILTERS FUNCTION ------------
void RemoveFilters_1(){

    // Filter is the first element in vectors
    vector<vector<float>> points = {
        {1.0, 9.0, 3.0, 4.0, 5.0, 6.0, 7.0},
        {2.0, 8.0, 3.0, 4.0, 5.0, 6.0, 7.0}
    };

    cout << endl << "Vectors with filter in first element: " << endl;

    for (const auto& row : points) {
        for (const auto& value : row) {
            cout << value << " ";
        }
        cout << endl;
    }

    RemoveFilters(points);

    cout << endl << "Vectors without filter in first element: " << endl;

    for (const auto& row : points) {
        for (const auto& value : row) {
            cout << value << " ";
        }
        cout << endl;
    }

    // Every vector size must be 6
    TEST_ASSERT(points[0].size() == (long unsigned int) 6);  
}


// ------------ FIND START NODE FUNCTION ------------
/*Test 1*/
void findStartNodeFromFilter_1(){

    vector<Map> STf = {
        {1.0 , 300},
        {2.0 , 106},
        {3.0 , 250}
    };

    float filter = 1.0;
    cout << endl << "Filter: " << filter << " with start node ";

    int s_node = findStartNodeFromFilter(STf,filter);
    cout << s_node << endl;

    // The start node for filter 1.0 must be 300
    TEST_ASSERT(s_node==300);  
}


/*Test 2*/
void findStartNodeFromFilter_2(){

    vector<Map> STf = {
        {1.0 , 300},
        {2.0 , 106},
        {3.0 , 250}
    };

    float filter = 3.0;
    cout << endl << "Filter: " << filter << " with start node ";

    int s_node = findStartNodeFromFilter(STf,filter);
    cout << s_node << endl;

    // The start node for filter 3.0 must be 250
    TEST_ASSERT(s_node==250);  
}


// ------------ RAND POINTS FUNCTION (IN MEDOID) ------------
void RandomPoints_1(){

    vector<int> points = {
        {56},
        {4},
        {300},
        {2},
        {1},
        {90},
        {12}
    };

    int threshold = 3;
    cout << endl << "Threshold: " << threshold << endl;

    cout << "Points in vector: " << endl; 
    for(size_t i = 0; i < points.size(); i ++){
        
        cout << points[i] << " ";
    }

    // Choose 3 random points from vector
    vector<int> rand_points = randompoints(points,threshold);

    cout << endl << endl << threshold << " random points choosen from vector:" << endl;
    for(size_t i = 0; i < rand_points.size(); i ++){
        
        cout << rand_points[i] << " ";
    }

    // Random points must be 3 in size
    TEST_ASSERT(rand_points.size() == (long unsigned int) 3);  
}


// ------------ FIND MEDOID ALGORITHM ------------
void FindMedoid_1(){

    // The first element in every vector is the filter
    vector<vector<float>> nodes = {
        {11.0, 1.3, 3.0, 4.0, 5.0, 6.0, 7.0},
        {34.0, 1.3, 3.0, 4.0, 5.0, 6.0, 7.0},
        {34.0, 1.3, 3.0, 4.0, 5.0, 6.0, 7.0},
        {11.0, 1.3, 3.0, 4.0, 5.0, 6.0, 7.0},
        {34.0, 1.3, 3.0, 4.0, 5.0, 6.0, 7.0},
        {6.0, 1.3, 3.0, 4.0, 5.0, 6.0, 7.0},
        {6.0, 1.3, 3.0, 4.0, 5.0, 6.0, 7.0},
        {34.0, 1.3, 3.0, 4.0, 5.0, 6.0, 7.0},
        {34.0, 1.3, 3.0, 4.0, 5.0, 6.0, 7.0}
    };

    int threshold = 3;

    // Create a start node map 
    vector<Map> STf = FindMedoid(nodes, threshold);

    cout << endl << "We have 3 different filters in dataset" << endl;
    cout << "Map of start nodes for every filter" << endl;
    PrintMedoidMap(STf);

    // Medoid map must have 3 start points (one start point per filter)
    TEST_ASSERT(STf.size() == (long unsigned int) 3); 
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


// ------------ FILTERED GREEDY SEARCH FUNCTION ------------

/* Test 1 - Just testing if Greedy finds the wright k neighbors (all same filters)*/
void FilteredGreedySearch_Test_1() {
  vector<vector<float>> points = {
        {1.0, 2.0},
        {2.0, 1.0},
        {0.0, 2.0},
        {1.0, 1.0},
        {1.0, 0.0}
    };

    vector<graph> G(5);

    // Add neighbors
    G[0].neighbors.push_back({1, 1.5});
    G[0].neighbors.push_back({2, 2.9});
    G[1].neighbors.push_back({0, 1.3});
    G[2].neighbors.push_back({0, 2.6});
    G[2].neighbors.push_back({4, 1.5});
    G[3].neighbors.push_back({1, 3.5});
    G[3].neighbors.push_back({2, 4.5});
    G[4].neighbors.push_back({0, 2.5});
    G[4].neighbors.push_back({2, 1.5});

    // Filters for the nodes
    G[0].filter = 1.0;
    G[1].filter = 1.0;
    G[2].filter = 1.0;
    G[3].filter = 1.0;
    G[4].filter = 1.0;

    vector<Map> medoids = {  {1.0, 3} };      // Start search at node for filter 1.0 is 3
    vector<float> q = {0.0, 0.0};             // Using query point different from the points of vector
    float query_filter = 1.0;                 // Filter of query point
    int k = 2;
    int L = 4;

   auto [K_neighbors, visited_nodes] = FilteredGreedySearch(medoids, q, k, L, points, G, query_filter);

    cout << "\nGreedy search result:" << endl;
    print(K_neighbors, visited_nodes);

    // 2 nearest neighbors to q must be points[3] and points[4]
    TEST_ASSERT(K_neighbors.size() == 2);
}


/* Test 2 - Testing if Greedy finds the wright k neighbors (different filters)*/
void FilteredGreedySearch_Test_2() {
  vector<vector<float>> points = {
        {1.0, 2.0},
        {2.0, 1.0},
        {0.0, 2.0},
        {1.0, 1.0},
        {1.0, 0.0}
    };

    vector<graph> G(5);

    // Add neighbors
    G[0].neighbors.push_back({1, 1.5});
    G[0].neighbors.push_back({2, 2.9});
    G[1].neighbors.push_back({0, 1.3});
    G[2].neighbors.push_back({0, 2.6});
    G[2].neighbors.push_back({4, 1.5});
    G[3].neighbors.push_back({1, 3.5});
    G[3].neighbors.push_back({2, 4.5});
    G[4].neighbors.push_back({0, 2.5});
    G[4].neighbors.push_back({2, 1.5});

    // Filters for the nodes
    G[0].filter = 1.0;
    G[1].filter = 1.0;
    G[2].filter = 1.0;
    G[3].filter = 1.0;
    G[4].filter = 2.0;      // Different filter

    vector<Map> medoids = {
        {1.0, 3},            // Start search at node for filter 1.0 is 3
        {2.0, 4}
    };    
    
    vector<float> q = {0.0, 0.0};             // Using query point different from the points of vector
    float query_filter = 1.0;                 // Filter of query point
    int k = 2;
    int L = 8;

   auto [K_neighbors, visited_nodes] = FilteredGreedySearch(medoids, q, k, L, points, G, query_filter);

    cout << "\nGreedy search result:" << endl;
    print(K_neighbors, visited_nodes);

    cout << "NOTE: Node 4 has different filter from query and should NOT be visited" << endl;

    // points[3] should exists in k=2 nearest neighbors BUT NOT points[4]
    TEST_ASSERT(K_neighbors.size() == 2);
}


/* Test 3 - Testing if Greedy finds the wright k neighbors (unfiltered query, query point exists in dataset)*/
void FilteredGreedySearch_Test_3() {
  vector<vector<float>> points = {
        {1.0, 2.0},
        {2.0, 1.0},
        {0.0, 2.0},
        {1.0, 1.0},
        {1.0, 0.0},
        {5.0, 8.0},
        {0.0, 0.0}
    };

    vector<graph> G(7);

    // Add neighbors
    G[0].neighbors.push_back({1, 1.5});
    G[0].neighbors.push_back({2, 2.9});
    G[1].neighbors.push_back({0, 1.3});
    G[2].neighbors.push_back({0, 2.6});
    G[2].neighbors.push_back({4, 1.5});
    G[3].neighbors.push_back({1, 3.5});
    G[3].neighbors.push_back({2, 4.5});
    G[4].neighbors.push_back({0, 2.5});
    G[4].neighbors.push_back({2, 1.5});
    G[5].neighbors.push_back({6, 8.0});
    G[6].neighbors.push_back({5, 8.0});

    // Filters for the nodes
    G[0].filter = 1.0;
    G[1].filter = 1.0;
    G[2].filter = 1.0;
    G[3].filter = 1.0;
    G[4].filter = 2.0;      // Different filter
    G[5].filter = 3.0;      // Different filter
    G[6].filter = 3.0;

    // Medoid map for filters
    vector<Map> medoids = {
        {1.0, 3},
        {2.0, 4},
        {3.0, 5}
    };      

    vector<float> q = {0.0, 0.0};             // Query point
    float query_filter = -1.0;                // Filter of query point
    int k = 4;
    int L = 6;

   auto [K_neighbors, visited_nodes] = FilteredGreedySearch(medoids, q, k, L, points, G, query_filter);

    cout << "\nGreedy search result:" << endl;
    print(K_neighbors, visited_nodes);

    // points[6] must be the first nearest neighbor (the same as query)
    TEST_ASSERT(K_neighbors.size() == 4);
}


/* Test 4 - Testing if Greedy finds the wright k neighbors (unfiltered query, query point doesn't exists in dataset)*/
void FilteredGreedySearch_Test_4() {
  vector<vector<float>> points = {
        {1.0, 2.0},
        {2.0, 1.0},
        {0.0, 2.0},
        {1.0, 1.0},
        {1.0, 0.0},
        {5.0, 8.0},
        {9.0, 9.0}
    };

    vector<graph> G(7);

    // Add neighbors
    G[0].neighbors.push_back({1, 1.5});
    G[0].neighbors.push_back({2, 2.9});
    G[1].neighbors.push_back({0, 1.3});
    G[2].neighbors.push_back({0, 2.6});
    G[2].neighbors.push_back({4, 1.5});
    G[3].neighbors.push_back({1, 3.5});
    G[3].neighbors.push_back({2, 4.5});
    G[4].neighbors.push_back({0, 2.5});
    G[4].neighbors.push_back({2, 1.5});
    G[5].neighbors.push_back({6, 8.0});
    G[6].neighbors.push_back({5, 8.0});

    // Filters for the nodes
    G[0].filter = 1.0;
    G[1].filter = 1.0;
    G[2].filter = 1.0;
    G[3].filter = 1.0;
    G[4].filter = 2.0;      // Different filter
    G[5].filter = 3.0;      // Different filter
    G[6].filter = 3.0;

    // Medoid map for filters
    vector<Map> medoids = {
        {1.0, 3},
        {2.0, 4},
        {3.0, 5}
    };      

    vector<float> q = {0.0, 0.0};             // Query point that doesn't exists in dataset
    float query_filter = -1.0;                // Filter of query point
    int k = 4;
    int L = 6;

   auto [K_neighbors, visited_nodes] = FilteredGreedySearch(medoids, q, k, L, points, G, query_filter);

    cout << "\nGreedy search result:" << endl;
    print(K_neighbors, visited_nodes);

    // points[3] and points[4] must be the first nearest neighbors
    TEST_ASSERT(K_neighbors.size() == 4);
}


// ------------ FILTERED VAMANA ALGORITHM ------------
void FilteredVamana_1(){

    // Setup dataset with 2 different filters
    vector<vector<float>> data = {
        {1.0, 1.0, 1.0}, // 0 
        {1.0, 2.0, 2.0}, // 1
        {1.0, 3.0, 2.0}, // 2
        {1.0, 6.0, 2.0}, // 3
        {1.0, 8.0, 2.0}, // 4
        {1.0, 5.0, 9.3}, // 5
        {2.0, 3.0, 3.0}, // 6
        {2.0, 5.0, 5.0}, // 7
        {2.0, 3.8, 2.1}, // 8
        {2.0, 3.9, 3.0}, // 9
        {2.0, 5.0, 5.2}, // 10
        {2.0, 7.0, 2.1}  // 11
    };

    float a = 1.2;
    int L = 10;
    int R = 5;
    int t = 3;

    vector<Map> STf = {
        {1.0, 2},
        {2.0, 9}
    };

   vector <graph> G_Filtered = FilteredVamana(data,a,L,R,t,STf);

    cout << endl << " Max out-neighbors for every node must be <= 5" << endl;
    PrintGraph(G_Filtered);

    // Check the size of neighbors in every node
    bool flag = 0;
    for(size_t i = 0; i < G_Filtered.size(); i++){

        int ns = G_Filtered[i].neighbors.size();
        if(ns > R){
            flag = 1;
        }
    }

    // Max out-neighbors for every node must be <= R_stitched
    TEST_ASSERT(flag == 0); 
}


// ------------ STITCHED VAMANA ALGORITHM ------------
void StitchedVamana_1(){

    // Setup dataset with 2 different filters
    vector<vector<float>> data = {
        {1.0, 1.0, 1.0}, // 0 
        {1.0, 2.0, 2.0}, // 1
        {1.0, 3.0, 2.0}, // 2
        {1.0, 6.0, 2.0}, // 3
        {1.0, 8.0, 2.0}, // 4
        {1.0, 5.0, 9.3}, // 5
        {2.0, 3.0, 3.0}, // 6
        {2.0, 5.0, 5.0}, // 7
        {2.0, 3.8, 2.1}, // 8
        {2.0, 3.9, 3.0}, // 9
        {2.0, 5.0, 5.2}, // 10
        {2.0, 7.0, 2.1}  // 11
    };

    float a = 1.2;
    int L_small = 10;
    int R_small = 4;
    int R_stitched = 1;

    vector<Map> STf = {
        {1.0, 2},
        {2.0, 9}
    };

    vector <graph> G_stitched = StitchedVamana(data, a, L_small, R_small, R_stitched, STf);

    cout << endl << " Max out-neighbors for every node must be <= 4, except start nodes may have extra neighbors (R_small + R_stitched)." << endl;
    PrintGraph(G_stitched);

    // Check the size of neighbors in every node
    bool flag = 0;
    int node = -1;
    for(size_t i = 0; i < G_stitched.size(); i++){

        int ns = G_stitched[i].neighbors.size();
        if(ns > R_small){
            flag = 1;
            node = i;
        }
    }

    // Max out-neighbors for every node must be <= R_stitched (except start nodes neighbors)
    TEST_ASSERT((flag == 1) && ((node == 9) || (node == 2) || (node ==-1))); 
}




/* Test Main */
TEST_LIST = {

    // Euclidean Distance Tests
    {"Euclidean Distance (test 1)", EuclideanDistance_1},
    {"Euclidean Distance (test 2)", EuclideanDistance_2},

    // ------ TESTING OLD VAMANA ALGORITHMS ------
    
    // Create Graph Tests
    {"Create Graph",  CreateGraph_1},

    // Greedy Search Tests
    {"Greedy Search (test 1)", GreedySearch_1},
    {"Greedy Search (test 2)", GreedySearch_2},

    // Robust Prune Tests
    {"Robust Prune", RobustPrune_1},

    // -------------------------------------------

    // Clean Data Tests
    {"Clean Data", CleanData_1},

    // Clean Queries Tests
    {"Clean Queries", CleanQueries_1},

    // Remove Filters Tests
    {"Remove Filters", RemoveFilters_1},

    // Find Start Node from Filter Tests
    {"Find Start Node from Filter (test 1)", findStartNodeFromFilter_1},
    {"Find Start Node from Filter (test 2)", findStartNodeFromFilter_2},

    // Random Points in medoid funtion Tests
    {"Random Points (in medoid, using threshold)", RandomPoints_1},

    // Find Medoid Tests
    {"Find Medoid", FindMedoid_1},

    // Filtered Robust Prune Tests
    {"Filtered Robust Prune (test 1)", FilteredRobustPrune_Test_1},
    {"Filtered Robust Prune (test 2)", FilteredRobustPrune_Test_2},
    {"Filtered Robust Prune (test 3)", FilteredRobustPrune_Test_3},
    {"Filtered Robust Prune (test 4)", FilteredRobustPrune_Test_4},

    // Filtered Greedy Search Tests
    {"Filtered Greedy Search (test 1)", FilteredGreedySearch_Test_1},
    {"Filtered Greedy Search (test 2)", FilteredGreedySearch_Test_2},
    {"Filtered Greedy Search (test 3)", FilteredGreedySearch_Test_3},
    {"Filtered Greedy Search (test 4)", FilteredGreedySearch_Test_4},

    //Filtered Vamana Tests
    {"Filtered Vamana Algorithm", FilteredVamana_1},

    //Stitched Vamana Tests
    {"Stitched Vamana Algorithm", StitchedVamana_1},
    

    {NULL, NULL}
};