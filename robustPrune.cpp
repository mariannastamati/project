#include "robustPrune.h"


vector<vector<edge>> RobustPrune(int p, vector<int>& V, float a, int R, vector<vector<edge>>& Graph, const vector<vector<float>>& data) {
    vector<int> N_out;  // Neighbors of p (To keep the final neighbors)

    // Create a temporary vector to store previous neighbors of p
    vector<int> previous_neighbors;

    // Store previous neighbors of p
    for (const auto& edge : Graph[p]) {

        // Check if the neighbor already exists in V
        if (find(V.begin(), V.end(), edge.first) == V.end()){
            previous_neighbors.push_back(edge.first);
        }
        
    }

    // Remove p from V if it exists
    V.erase(remove(V.begin(), V.end(), p), V.end());

    // Add previous neighbors of p to V
    V.insert(V.end(), previous_neighbors.begin(), previous_neighbors.end());

    while (!V.empty()) {
        // Find the closest point to p
        int p_star = *std::min_element(V.begin(), V.end(), [&](int p1, int p2) {
            return EuclideanDistance(data[p], data[p1]) < EuclideanDistance(data[p], data[p2]);
        });

        // Add p_star to the neighbors
        N_out.push_back(p_star);
        //std::cout << "Adding node " << p_star << " as a neighbor of " << p << "." << std::endl;

        // Stop if we've reached the limit
        if (N_out.size() == static_cast<size_t>(R)) {
            break;
        }

        // Remove p_star from V
        V.erase(remove(V.begin(), V.end(), p_star), V.end());
        
        // Prune V based on distance
        int vsize = V.size();
        // For every p' in V
        for(int i = 0; i < vsize; i++){

            // Calculate Euclidean distance for (p*,p') and (p,p')
            float Dist_pstar = EuclideanDistance(data[p_star], data[V[i]]);
            float Dist_p = EuclideanDistance(data[p], data[V[i]]);

            // If this is true then remove p' from V
            if((a*Dist_pstar) <= Dist_p){

                // Remove p' from V
                V.erase(remove(V.begin(), V.end(), V[i]), V.end());
            }
        }
    }

    // Update the graph with the new neighbors for p
    Graph[p].clear();               // Clear existing neighbors for node p
    for (int neighbor : N_out) {
        float distance = EuclideanDistance(data[p], data[neighbor]);

        // Add new neighbors for node p in Graph
        Graph[p].emplace_back(neighbor, distance);
    }

    // Ensure we are filling in less than R neighbors
    if (N_out.size() > static_cast<size_t>(R)) {
        cout << "Warning: More than " << R << " neighbors found for node " << p << ". Prune gone wrong." << endl;
    }

    return Graph;  // Return the updated graph
}
