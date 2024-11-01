#include <iostream>
#include "acutest.h"
#include "VamanaIndexing.h"
#include "printGraph.h"

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


//---------------- MEDOID FUNCTION ----------------
/* Test 1 */
void Medoid_1(){
    
    vector<vector<float>> points = {
        {1.0, 2.0},
        {2.0, 1.0},
        {0.0, 2.0},
        {0.0, 1.0}
    };

    int s = Medoid(points);

    // Medoid is points[0]
    TEST_ASSERT(s == 0);
}


/* Test 2 */
void Medoid_2(){
    
    vector<vector<float>> points = {
        {1.0, 2.0},
        {2.0, 1.0},
        {0.0, 2.0},
        {1.0, 1.0},
        {1.0, 0.0}
    };

    int s = Medoid(points);

    // Medoid is points[3]
    TEST_ASSERT(s == 3);
}


//------------ CREATE R-DIRECTED GRAPH ------------
/* Test 1 */
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


/* Test 3 */
void GreedySearch_3(){

    vector<vector<float>> points = {
        {1.0, 2.0},
        {2.0, 1.0},
        {0.0, 2.0},
        {1.0, 1.0},
        {1.0, 0.0}
    };

    int medoid = 3;
    vector<vector<edge>> G = CreateGraph(points, points.size(), 3);
    vector<float> q = {2.0, 2.0};       // Using query point different from the points of vector
    int k = 2;
    int L = 3;

    auto [K_neighbors, visited_nodes] = GreedySearch(medoid, q, k, L, points, G);

    cout << "\nGreedy search result:" << endl;
    print(K_neighbors, visited_nodes);

    // 2 nearest neighbors to q must be points[1] and points[0]
    TEST_ASSERT(K_neighbors.size() == (long unsigned int) k);
}


// ------------ ROBUST PRUNE ALGORITHM ------------
/* Test 1 */ 
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

    cout << "\nbefore:" << endl;
    PrintGraph(G); // Print the initial graph

    // Run the Greedy Search to get the visited nodes set
    auto [K_neighbors, visited_nodes] = GreedySearch(medoid, q, k, L, points, G);

    cout <<"K-neighbors and Visited nodes from greedy: " << endl;
    print(K_neighbors, visited_nodes);

    // TEST TO PRUNE MEDOID NODE, points[3]
    vector<int> V = visited_nodes;
    // Now use the output of the greedy search as input to the prune function
    G = RobustPrune(medoid, V, a, R, G, points); // Perform Robust Prune
        
    cout << "\nRobust Prune result:" << endl;
    PrintGraph(G); // Print the updated graph after pruning

    // Assertions to check the expected outcomes
    TEST_ASSERT(G[medoid].size() < static_cast<size_t>(R)); // Check that the number of neighbors is less than R

    for (const edge& e : G[medoid]) {
        int neighbor = e.first;
        TEST_ASSERT(neighbor != 5 && neighbor != 6); // Ensure no outliers are included as neighbors
    }
}


// Test 2
void RobustPrune_2() {
    vector<vector<float>> points = {
        {1.0, 2.0},
        {2.0, 1.0},
        {0.0, 2.0},
        {1.0, 1.0},
        {1.0, 0.0},
        {1000.0, 1000.0},    // Outlier (Point 5)
        {500.0, 500.0}      // Another outlier (Point 6)
    };
    
    int medoid = 3;                 // Use point {1.0, 1.0} as medoid
    int R = 4;                      // Max out-neighbors
    float a = 1.0;                  // Pruning threshold
    vector<float> q = {2.0, 2.0};   // Query point
    int k = 3;
    int L = 5;

    vector<vector<edge>> G = CreateGraph(points, points.size(), R); // Create a graph with R neighbors

    cout << "\nbefore:" << endl;
    PrintGraph(G); // Print the initial graph

    // Run the Greedy Search to get the visited nodes set
    auto [K_neighbors, visited_nodes] = GreedySearch(medoid, q, k, L, points, G);

    cout <<"K-neighbors and Visited nodes from greedy: " << endl;
    print(K_neighbors, visited_nodes);

    // TEST TO PRUNE NODE 0, points[]
    vector<int> V = visited_nodes;
    // Now use the output of the greedy search as input to the prune function
    G = RobustPrune(0, V, a, R, G, points); // Perform Robust Prune
        
    cout << "\nRobust Prune result:" << endl;
    PrintGraph(G); // Print the updated graph after pruning

    // Assertions to check the expected outcomes
    TEST_ASSERT(G[0].size() < static_cast<size_t>(R)); // Check that the number of neighbors is less than R
}









/* Test Main */
TEST_LIST = {

    // Euclidean Distance Tests
    {"Euclidean Distance 1", EuclideanDistance_1},
    {"Euclidean Distance 2", EuclideanDistance_2},

    // Medoid Tests
    {"Medoid 1", Medoid_1},
    {"Medoid 2", Medoid_2},

    // Create Graph Tests
    {"Create Graph 1", CreateGraph_1},

    // Greedy Search Tests
    {"Greedy Search 1", GreedySearch_1},
    {"Greedy Search 2", GreedySearch_2},
    {"Greedy Search 3", GreedySearch_3},

    // Robust Prune Tests
    {"Robust Prune 1", RobustPrune_1},
    {"Robust Prune 1", RobustPrune_2},

    {NULL, NULL}
};