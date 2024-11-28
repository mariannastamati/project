#include <iostream>
#include "acutest.h"
#include "FilteredVamana.h"
#include "StitchedVamana.h"
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
    TEST_ASSERT(points[0].size()==2);
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
    TEST_ASSERT((points.size()==3) && (points[0].size()==5));     
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
    TEST_ASSERT(points[0].size()==6);  
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
    TEST_ASSERT(rand_points.size()==3);  
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
    TEST_ASSERT(STf.size()==3); 
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
    

    {NULL, NULL}
};