#include "FilteredGreedySearch.h"

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
    const float filter){ 


    vector<int> visited;        // Set for the nodes we have visited (empty)
    vector<int> List;           // Search list which we initialize with the start node

    bool flag = 0;              // Flag for filtered queries (if filter of query exists in dataset)
    
    // If filter > -1 then we have filtered query
    if(filter > -1){

        // Iterate over medoids and filters, and add the node_id to List if it satisfies the filter
        for (const auto& medoid : medoids){
            
            if(medoid.filter==filter){ 

                List.push_back(medoid.start_node);
                flag = 1;       // Medoid found, filter exists in dataset
            }       
        }

    // Else we have unfiltered query (search in every node with every filter)
    }else{

        flag = 1;       // Filter exists (unfiltered query satisfies every filter)

        // Iterate over medoids and filters, and add all the start nodes in search list L
        for (const auto& medoid : medoids){
            
            List.push_back(medoid.start_node);    
        }
    }


    // If filter of query doesn't exist in dataset then return (we can't find neighbors)
    if(flag == 0){

        cout << "Query with filter: " << static_cast<int>(filter) << ". This filter does not exist in graph." << endl;
        return make_pair(List, visited);
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

        // Update visited <- visited + p* (pstar)
        if(find(visited.begin(), visited.end(), pstar) == visited.end()){
            visited.push_back(pstar);
        }

        // Update list <- list + (neighbors of p* (pstar))
        for (const auto& e : graph[pstar].neighbors){

            // Get the node_id from the edge pair
            int neighbor_id = e.first;     

            // If query is filtered, check filters
            if(filter > -1){

                // Check if the node has the same filter as query and has not been visited
                if ((graph[neighbor_id].filter == filter) && (find(visited.begin(), visited.end(), neighbor_id) == visited.end())
                && (find(List.begin(), List.end(), neighbor_id) == List.end())){
                    
                    List.push_back(neighbor_id); // Add the node to List
                }

            // If query is unfiltered don't check in filters
            }else{

                if((find(visited.begin(), visited.end(), neighbor_id) == visited.end())
                && (find(List.begin(), List.end(), neighbor_id) == List.end())){
                    List.push_back(neighbor_id); // Add the node to List
                }
            }
        }

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

    // Sort closest points in L and keep only k closest
    sort(List.begin(), List.end(), [&query, &vectors](int a, int b){
        return EuclideanDistance(vectors[a], query) < EuclideanDistance(vectors[b], query);
    });

    // If List size is greater than k return only k, else return the whole list
    int Lsize = List.size();
    if(Lsize > k){

        List.resize(k); // We return only the k closest points
    }

    // Return result
    return make_pair(List, visited);
}