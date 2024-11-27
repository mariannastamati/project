#include "FilteredRobustPrune.h"
#include "graph.h"

vector <graph> FilteredRobustPrune(int currentPoint, vector<int>& visited_nodes, float a, int R, vector<graph>& G, const vector<vector<float>>& data)
{
    vector<int> N_out; // Stores the selected neighbors for the current node
    vector<int> previous_neighbors; // Stores unvisited neighbors of the current node

    // Add all unvisited neighbors of the current node to previous_neighbors
    for (const auto& edge : G[currentPoint].neighbors)
    {
        if (find(visited_nodes.begin(), visited_nodes.end(), edge.first) == visited_nodes.end())
        {
            previous_neighbors.push_back(edge.first);
        }
    }

    // Remove the current node from the list of visited nodes
    visited_nodes.erase(remove(visited_nodes.begin(), visited_nodes.end(), currentPoint), visited_nodes.end());

    // Add previous neighbors to the visited nodes list
    visited_nodes.insert(visited_nodes.end(), previous_neighbors.begin(), previous_neighbors.end());

    // Process nodes until the visited nodes list is empty
    while (!visited_nodes.empty())
    {
        int p_star = -1; // The closest node to currentPoint
        double min_distance = INFINITY; // Initialize minimum distance as infinity

        int size = visited_nodes.size();

        // Find the closest node in visited_nodes to currentPoint
        for (int i = 0; i < size; i++)
        {
            double dist = EuclideanDistance(data[visited_nodes[i]], data[currentPoint]);
            if (dist < min_distance)
            {
                min_distance = dist;
                p_star = visited_nodes[i];
            }
        }

        N_out.push_back(p_star); // Add the closest node to N_out

        // Stop if the out-degree limit R is reached
        if (N_out.size() == R)
        {
            break;
        }

        // Remove p_star from visited_nodes
        visited_nodes.erase(remove(visited_nodes.begin(), visited_nodes.end(), p_star), visited_nodes.end());

        int vsize = visited_nodes.size();

        // Filter out nodes based on the distance condition
        for (int i = 0; i < vsize; i++)
        {
            int p_prime = visited_nodes[i];
            
            // Check if filters intersect; if not, skip this node
            if (G[p_prime].filter != G[p_star].filter)
            {
                continue; // Skip nodes with non-overlapping filters
            }

            double dist_p_star = EuclideanDistance(data[p_star], data[p_prime]);
            double dist_p = EuclideanDistance(data[currentPoint], data[p_prime]);

            // Remove node if it violates the condition
            if (a * dist_p_star <= dist_p)
            {
                visited_nodes.erase(remove(visited_nodes.begin(), visited_nodes.end(), p_prime), visited_nodes.end());
            }
        }
    }

    // Update the neighbors of currentPoint in the graph
    G[currentPoint].neighbors.clear(); // Clear existing neighbors
    for (size_t i = 0; i < N_out.size(); i++)
    {
        int neighbor = N_out[i];
        double distance = EuclideanDistance(data[currentPoint], data[neighbor]);

        G[currentPoint].neighbors.emplace_back(neighbor, distance); // Add new neighbors
    }

    return G; // Return the updated graph
}
