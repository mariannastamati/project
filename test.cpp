#include <iostream>
#include "acutest.h"
#include "VamanaIndexing.h"

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




/* Test Main */
TEST_LIST = {

    // Euclidean Distance Tests
    {"Euclidean Distance 1", EuclideanDistance_1},
    {"Euclidean Distance 2", EuclideanDistance_2},

    // Medoid Tests
    {"Medoid 1", Medoid_1},
    {"Medoid 2", Medoid_2},

    // Greedy Search Tests
    {"Greedy Search 1", GreedySearch_1},
    {"Greedy Search 2", GreedySearch_2},
    {"Greedy Search 3", GreedySearch_3},

    {"Greedy Search 4 Marianna", GreedySearch_4},
    {NULL, NULL}
};