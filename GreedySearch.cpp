#include "GreedySearch.h"
#include "graph.h"
#include <queue>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

// Function to compare two nodes (a, b) and select the closest one 
bool compare(int a, int b, const vector<float>& query, const vector<vector<float>>& vectors) {
    return EuclideanDistance(query, vectors[a]) > EuclideanDistance(query, vectors[b]);
}

// Greedy Search 
pair<vector<int>, set<int>> GreedySearch(const vector<vector<edge>>& graph, const vector<float>& query, const vector<vector<float>>& vectors, int start_node, int k, int L) {

    set<int> visited;                 // Set for the nodes we have visited
    vector<int> result_set;           // Result set 
    vector<int> search_list = {start_node};   // Search list which we initialize with the start node 
    
    visited.insert(start_node);       

    // Sorting the search list based on the distance from the query
    sort(search_list.begin(), search_list.end(), [&](int a, int b) {
        return compare(a, b, query, vectors);  
    });

    // Comparison function for priority queque
    auto comp = [&](int a, int b) {
        return EuclideanDistance(query, vectors[a]) > EuclideanDistance(query, vectors[b]);
    };

    priority_queue<int, vector<int>, decltype(comp)> pq(comp);
    
    while (!search_list.empty()) {

        // Finding the nearest p* node from non-visitors
        int closest = search_list.back();
        search_list.pop_back();
        
        // Add all neighbours of the closest node to the search list
        for (const auto& neighbor : graph[closest]) {
            int neighbor_node = neighbor.first;
            
            // If the node has not already been visited, add it to the list
            if (visited.find(neighbor_node) == visited.end()) {
                visited.insert(neighbor_node);
                search_list.push_back(neighbor_node);

                // Insert the new node in priority_queue to keep only the k closest nodes
                pq.push(neighbor_node);

                // Keep only the L best
                int pq_size = pq.size();
                if (pq_size > L) {
                    pq.pop();
                }
            }
        }
    }

    // Return of the k nearest nodes
    while (!pq.empty()) {
        result_set.push_back(pq.top());
        pq.pop();
    }

    // We keep only the k closest nodes and return them
    sort(result_set.begin(), result_set.end(), comp);
    int r_set = result_set.size();
    if (r_set > k) {
        result_set.resize(k);
    }

    return make_pair(result_set, visited);  // Return the result set and the visited set
}
