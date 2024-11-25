#include "GreedySearch.h"


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


// Greedy Search Algorithm
pair<vector<int>, vector<int>> GreedySearch(int medoid, const vector<float>& query, int k, int L, const vector<vector<float>>& vectors,
const vector<vector<edge>>& graph){

    vector<int> visited;              // Set for the nodes we have visited (empty)
    vector<int> List = {medoid};      // Search list which we initialize with the start node 
    
    vector<int> L_without_V = removeCommonElements(visited,List);   // L\V

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
        for (const auto& e : graph[pstar]){
            if(find(List.begin(), List.end(), e.first) == List.end())
                List.push_back(e.first);
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