#include "robustPrune.h"
#include <limits>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "printGraph.h"
#include "graph.h"

std::vector<std::vector<edge>> RobustPrune(int p, std::vector<int>& V, float a, int R, std::vector<std::vector<edge>>& Graph, const std::vector<std::vector<float>>& data) {
    std::vector<int> N_out;  // Neighbors of p

    // Create a temporary vector to store previous neighbors of p
    std::vector<int> previous_neighbors;

    // Store previous neighbors before removing p from V
    for (const auto& edge : Graph[p]) {
        previous_neighbors.push_back(edge.first);
    }

    // Remove p from V if it exists
    V.erase(std::remove(V.begin(), V.end(), p), V.end());

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
            //std::cout << "Reached maximum neighbors for node " << p << "." << std::endl;
            break;
        }

        // Remove p_star from V
        V.erase(std::remove(V.begin(), V.end(), p_star), V.end());
        //std::cout << "Removed node " << p_star << " from candidates." << std::endl;

        // Prune V based on distance
        V.erase(std::remove_if(V.begin(), V.end(), [&](int candidate) {
            float dist_p_candidate = EuclideanDistance(data[p], data[candidate]);
            float dist_p_p_star = EuclideanDistance(data[p], data[p_star]);
            bool to_prune = dist_p_candidate > a * dist_p_p_star;

            // Debugging output for pruning decision
            // std::cout << "Checking candidate " << candidate << ": "
            //           << "Distance to p: " << dist_p_candidate << ", "
            //           << "Distance to p*: " << dist_p_p_star << ", "
            //           << "Prune condition: " << (to_prune ? "true" : "false") << std::endl;

            return to_prune;  // Returns true if it should be removed
        }), V.end());
    }

    // Update the graph with the new neighbors for p
    Graph[p].clear(); // Clear existing edges for node p
    for (int neighbor : N_out) {
        float distance = EuclideanDistance(data[p], data[neighbor]);
        Graph[p].emplace_back(neighbor, distance);
        //std::cout << "Setting edge from " << p << " to " << neighbor << " with distance " << distance << "." << std::endl;
    }

    // Ensure we are filling in R neighbors
    if (N_out.size() < static_cast<size_t>(R)) {
        std::cout << "Warning: Less than " << R << " neighbors found for node " << p << "." << std::endl;
    }

    std::cout << "Graph updated for node " << p << "." << std::endl;
    return Graph;  // Return the updated graph
}
