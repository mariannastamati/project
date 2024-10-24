#include "robustPrune.h"
#include "graph.h"
#include <limits>
#include <vector>
#include <algorithm>

#include "printGraph.h"

// RobustPrune algorithm implementation
std::vector<std::vector<edge>> RobustPrune(int p, std::vector<int>& V, float a, int R, std::vector<std::vector<edge>>& graph) {
    std::vector<int> N_out;  // N_out(p)
    V.erase(std::remove(V.begin(), V.end(), p), V.end());  // V ← (V ∪ N_out(p)) \ {p}

    N_out.clear();  // N_out(p) ← ∅

    while (!V.empty()) {
        // p* ← arg minp'∈V d(p, p')
        int p_star = V[0];
        float min_dist = std::numeric_limits<float>::max();

        // Find the closest neighbor in V using the precomputed distance in graph[p]
        for (int v : V) {


            // graph[p] = μια λίστα από τους γείτονες του p
            // πρέπει να κάνω αναζήτηση του v μέσα στο graph[p]
            /*vector<edge> &neighbors = graph[p];
            long unsigned int j;
            float dist = 0.0;
            for(j = 0; j < neighbors.size(); j++)
            {
                if(v == graph[p][j].first)
                {
                    dist = graph[p][j].second;
                    break;
                }
            }*/

            float dist = graph[p][v].second;  // Use precomputed distance from graph
            if (dist < min_dist) {
                min_dist = dist;
                p_star = v;
            }
        }

        // N_out(p) ← N_out(p) ∪ {p*}
        N_out.push_back(p_star);

        // Remove p* from V
        V.erase(std::remove(V.begin(), V.end(), p_star), V.end());

        // if |N_out(p)| = R then break
        if (N_out.size() == R) {
            break;
        }

        // for each p' ∈ V do
        for (auto it = V.begin(); it != V.end();) {
            int p_prime = *it;

            // Use precomputed distances for both d(p*, p') and d(p, p')
            float dist_star_prime = graph[p_star][p_prime].second;
            float dist_p_prime = graph[p][p_prime].second;

            // if a ⋅ d(p*, p') ≤ d(p, p') then remove p' from V
            if (a * dist_star_prime <= dist_p_prime) {
                it = V.erase(it);  // Remove p' from V
            } else {
                ++it;
            }
        }
    }

    // Now update the graph adjacency list by removing edges from node p that are not in N_out
    std::vector<edge> new_edges;
    for (const auto& neighbor : N_out) {
        // Find and keep only the edges to the selected neighbors in N_out
        for (const auto& e : graph[p]) {
            if (e.first == neighbor) {
                new_edges.push_back(e);
            }
        }
    }

    // Update the adjacency list of node p in the graph
    graph[p] = new_edges;
    
    // Return the entire modified graph
    return graph;
}


