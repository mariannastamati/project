#include "FilteredGreedySearch.h"

#include <cmath>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

// double EuclideanDistance(const vector<float>& node1, const vector<float>& node2){

//     if (node1.size() != node2.size()) {
//         throw invalid_argument("Vectors have different size.");
//     }

//     double sum = 0.0;
//     int size = node1.size();
//     for (int i = 0; i < size; ++i){

//         double diff = (node1[i] - node2[i])*(node1[i] - node2[i]);
//         sum = sum + diff;
//     }
   
//     double Euclidean = sqrt(sum);
//     return Euclidean;
// } 

// Function to remove common elements
vector<int> removeCommonElements(const vector<int>& visited, const vector<int>& neighbors_list){
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
    const vector<vector<int>>& graph,
    const vector<fnode>& filters) { 

        vector<int> visited;              // Set for the nodes we have visited (empty)
        vector<int> List ;      // Search list which we initialize with the start node 
    

    // Iterate over medoids and filters, and add the node_id to List if it satisfies the filter
       for (const auto& medoid : medoids) {
        for (const auto& filter : filters) {
            // if (medoid.satisfiesFilter(filter.filter)) {
            //     List.push_back(medoid.node_id);
            //     break;
            // }
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
         for (const auto& e : graph[pstar]) {
           if (find(List.begin(), List.end(), e) == List.end()){
               // Check if the node passes the filter of any medoid
                for (const auto& medoid : medoids) {
                    if (medoid.filter==(vectors[e][0])) {
                        List.push_back(e);
                        break;
                    }
                }
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