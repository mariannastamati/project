#include <iostream>
#include "acutest.h"
#include "FilteredVamana.h"
#include "graph.h"

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



/* Test Main */
TEST_LIST = {

    // Euclidean Distance Tests
    {"Euclidean Distance 1", EuclideanDistance_1},
    {"Euclidean Distance 2", EuclideanDistance_2},

    // Medoid Tests
    {"Medoid 1", Medoid_1},
    {"Medoid 2", Medoid_2},

    {NULL, NULL}
};