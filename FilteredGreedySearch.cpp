#include "FilteredGreedySearch.h"
#include <fstream>
#include <iostream>

#include <cmath>
#include <algorithm>
#include <set>
#include <vector>

#include "graph.h"

using namespace std;


// Function to remove common elements
inline vector<int> removeCommonElements(const vector<int>& visited, const vector<int>& neighbors_list){
    vector<int> result; //  Variable to save result

    for (int num : neighbors_list){

        if (find(visited.begin(), visited.end(), num) == visited.end()) {
            // If num does not belong to visited, add to result
            result.push_back(num);
        }
    }
    return result;
}

    
 

//Filtered Greedy Search

pair<vector<int>, vector<int>> FilteredGreedySearch( const vector<Map>& medoids,
   const vector<float>& query, 
    int k, 
    int L, 
    const vector<vector<float>>& vectors,
    const vector<graph>& graph,
    const float filter) { 

        vector<int> visited;              // Set for the nodes we have visited (empty)
        vector<int> List ;      // Search list which we initialize with the start node 
    
     //graph[1].
    // Iterate over medoids and filters, and add the node_id to List if it satisfies the filter
       for (const auto& medoid : medoids) {
        
            if(medoid.filter==filter){ 
             List.push_back(medoid.start_node);
            }
           
    }

    vector<int> L_without_V = removeCommonElements(visited, List);
    // While L\V != empty
    while(!L_without_V.empty()){

        // For every p in L_without_V keep the min euclidean from p and query point
        double mindist = INFINITY;
        int pstar = -1;

        int size = L_without_V.size();
        for(int p = 0; p < size; p++){

            // Calculate Euclidean distance between p and query point
            double dist = EuclideanDistance(vectors[L_without_V[p]], query);

            // Keep min distance and p*
            if(dist < mindist){
                mindist = dist;
                pstar = L_without_V[p];
            }
        }

        // Update list <- list + (neighbors of p* (pstar))
        for (const auto& e : graph[pstar].neighbors) {
            int neighbor_id = e.first; // Get the node_id from the edge pair

         // Check if the node passes the filter and has not been visited
          if (vectors[neighbor_id][0] == filter && find(visited.begin(), visited.end(), neighbor_id) == visited.end()) {
             List.push_back(neighbor_id); // Add the node to List
          }
       }

        // Update visited <- visited + p* (pstar)
        visited.push_back(pstar);

        // Checking if List_size is greater than L
        int Lsize = List.size();
        if(Lsize > L){

            // Keep only the top L elements in List 
            sort(List.begin(), List.end(), [&query, &vectors](int a, int b){
                return EuclideanDistance(vectors[a], query) < EuclideanDistance(vectors[b], query);
            });
            List.resize(L); // Keep only the top L closest points
        }

        // Calculate L\V with the updated data
        L_without_V = removeCommonElements(visited,List);
    }


    sort(List.begin(), List.end(), [&query, &vectors](int a, int b){
        return EuclideanDistance(vectors[a], query) < EuclideanDistance(vectors[b], query);
    });
    List.resize(k); // We return only the k closest points


   return make_pair(List, visited);

    }