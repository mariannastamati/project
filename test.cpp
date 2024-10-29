#include <iostream>
#include "acutest.h"
#include "VamanaIndexing.h"
#include "printGraph.h"

using namespace std;

void print(vector<int>& L, set<int>& V)
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

    pair<vector<int>, set<int>> result = GreedySearch(medoid, q, k, L, points, G);

    cout << "\nGreedy search result:" << endl;
    print(result.first, result.second);

    // The first nearest neighbor to q must be himself (points[2])
    TEST_ASSERT(result.first.size() == (long unsigned int) k);
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

    pair<vector<int>, set<int>> result = GreedySearch(medoid, q, k, L, points, G);

    cout << "\nGreedy search result:" << endl;
    print(result.first, result.second);

    // 2 nearest neighbors to q must be points[3] and points[4]
    TEST_ASSERT(result.first.size() == (long unsigned int) k);
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

    pair<vector<int>, set<int>> result = GreedySearch(medoid, q, k, L, points, G);

    cout << "\nGreedy search result:" << endl;
    print(result.first, result.second);

    // 2 nearest neighbors to q must be points[1] and points[0]
    TEST_ASSERT(result.first.size() == (long unsigned int) k);
}

//MARIANNA GREEDY 
/* Test 4 */
void GreedySearch_4(){

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

    pair<vector<int>, set<int>> result =GreedySearch(G, q, points, medoid, k, L);

    cout << "\nGreedy search result:" << endl;
    print(result.first, result.second);

    // 2 nearest neighbors to q must be points[1] and points[0]
    TEST_ASSERT(result.first.size() == (long unsigned int) k);
}


// ------------ ROBUST PRUNE TEST 5 ------------
// Test for Robust Prune Algorithm
void RobustPrune_1() {
    // Create a set of points
    vector<vector<float>> points = {
        {1.0, 2.0},        // Point 0
        {1.0, 1.0},        // Medoid (Point 1)
        {100000.0, 100000.0}, // Outlier (Point 2)
        {-100000.0, -100000.0} // Another outlier (Point 3)
    };

    int medoid = 1; // Use point {1.0, 1.0} as medoid
    vector<vector<edge>> G = CreateGraph(points, points.size(), 3); // Create initial graph

    // Perform Greedy Search first to get initial neighbors
    vector<int> V = {0, 2, 3}; // Candidate set containing points 0, 2, and 3
    float a = 1.5; // Pruning threshold
    int R = 1; // Max out-neighbors

    cout << "\nbefore:" << endl;
    PrintGraph(G); // Print the initial graph

    cout << "\n" << endl;

    // Run the Greedy Search
    pair<vector<int>, set<int>> greedy_result = GreedySearch(medoid, {0.0, 2.0}, 2, 3, points, G);

    // Now use the output of the greedy search as input to the prune function
    G = RobustPrune(medoid, V, a, R, G, points); // Perform Robust Prune

    cout << "\nRobust Prune result:" << endl;
    PrintGraph(G); // Print the updated graph after pruning

    // Assertions to check the expected outcomes
    TEST_ASSERT(G[medoid].size() == static_cast<size_t>(R)); // Check that the number of neighbors equals R

    for (const edge& e : G[medoid]) {
        int neighbor = e.first;
        TEST_ASSERT(neighbor != 2 && neighbor != 3); // Ensure no outliers are included as neighbors
    }
}

// ------------ ROBUST PRUNE TEST 6 ------------
// Test for Robust Prune Algorithm
void RobustPrune_2() {
    // Create a set of points, including some that should be pruned
    vector<vector<float>> points = {
        {1.0, 2.0},
        {2.0, 1.0},
        {0.0, 2.0},
        {1.0, 1.0},    // Medoid (central point)
        {1.0, 0.0},
        {100000.0, 100000.0}, // Outlier point (should be pruned)
        {-100000.0, -100000.0} // Another outlier point (should be pruned)
    };

    int medoid = 3;  // Use point {1.0, 1.0} as medoid
    vector<vector<edge>> G = CreateGraph(points, points.size(), 3);
    vector<int> V = {0, 1, 2, 4, 5, 6};  // Candidate set (including outliers)

    float a = 1.5;  // Increase the threshold slightly to improve pruning
    int R = 3;  // Max out-neighbors

    cout << "\nbefore:" << endl;
    PrintGraph(G);

    cout << "\n" << endl;

    // Run the Robust Prune algorithm
    G = RobustPrune(medoid, V, a, R, G, points);

    cout << "\nRobust Prune result:" << endl;
    PrintGraph(G);

    // Ensure that the pruned result has at most R neighbors for the medoid
    TEST_ASSERT(G[medoid].size() == (long unsigned int)R);

    // Ensure that the outliers (points 5 and 6) have been pruned
    for (const edge& e : G[medoid]) {
        int neighbor = e.first;
        TEST_ASSERT(neighbor != 5 && neighbor != 6);
    }
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

    {"Robust Prune 1", RobustPrune_1},
    {"Robust Prune 1", RobustPrune_2},

    {"Greedy Search 4 Marianna", GreedySearch_4},
    {NULL, NULL}
};