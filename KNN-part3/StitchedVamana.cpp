#include "StitchedVamana.h"

// Stitched Vamana Indexing algorithm
vector <graph> StitchedVamana(vector<vector<float>> &nodes, float a, int L_small, int R_small, int R_stitched, vector<Map> STf){

    // Initialize G to an empty graph
    vector <graph> G;

    // Resize the vector to have P (size = nodes_size) positions (so we can write in every pos we want)
    int size = nodes.size();
    G.resize(size);

    // Vector Pf to keep every filter f, and the ids of all points matching filter f
    vector<fnode> Pf;

    // Initialize Pf with the first filter of the dataset
    fnode first_node;
    first_node.filter = nodes[0][0];
    first_node.matching_points.push_back(0);
    Pf.push_back(first_node);


    for(int i = 1; i < size; i++){

        // Check if filter already exists in Pf list
        bool found = false;
        for(auto& node : Pf){
            if (node.filter == nodes[i][0]){

                // If filter already exists just add node id to the matching points
                node.matching_points.push_back(i);
                found = true;           // Change found to True
                break;
            }
        }

        // If we have a new filter add it to Pf list
        if(!found){
            fnode new_node;
            new_node.filter = nodes[i][0];
            new_node.matching_points.push_back(i);
            Pf.push_back(new_node);
        }
    }

    // Temporary variable to keep only vectors without filters (for use in old Vamana)
    vector<vector<float>> temp = nodes;
    RemoveFilters(temp);

    // For each filter f, call Vamana (old) to build a graph (using only the nodes of filter f)
    size = Pf.size();
    for(int i = 0; i < size; i++){

        // Take the vectors (without filters) matching in nodes of Pf
        vector<vector<float>> pf_nodes;
        int pfsize = Pf[i].matching_points.size();

        // If the number of matching nodes for filter f is 1, then Gf is only one node
        if(pfsize == 1){

            // Create a graph with only one node and no neighbors
            vector<vector<edge>> Gf(1);

            // Take the only matching point
            int point = Pf[i].matching_points[0];

            // Add the filter to G graph
            G[point].filter = Pf[i].filter;

            // Transfer neighbors from Gf to G
            G[point].neighbors = Gf[0];

            continue;
        }

        vector<pair<int,int>> pf_mapping;         // A map to help find the wright node in the smaller dataset of filter f
        for(int j = 0; j < pfsize; j++){

            vector<float> node = temp[Pf[i].matching_points[j]];
            pf_nodes.push_back(node);

            // Match nodes from small dataset to nodes of large dataset 
            pf_mapping.push_back(make_pair(j,Pf[i].matching_points[j]));
        }

        // Get medoid (start node of filter)
        int medoid = STf[i].start_node;

        // Find the matching node of medoid in small dataset
        for (const auto& pair : pf_mapping){
            if (pair.second == medoid){

                medoid = pair.first;
                break;
            }
        }

        // If number of matching nodes for filter f is less than R_small, then set R_small to pfsize-1
        vector<vector<edge>> Gf;
        if(pfsize <= R_small){

            // Create a graph for filter f nodes (with less neighbors per node)
            int R_size = pfsize - 1;
            Gf = VamanaIndexing(pf_nodes,a,L_small,R_size,medoid);

        }else{

            // Create a graph for filter f nodes
            Gf = VamanaIndexing(pf_nodes,a,L_small,R_small,medoid);
        }


        // Transfer Gf hypograph and filter to G graph
        for(int j = 0; j < pfsize; j++){

            int point = pf_mapping[j].second;

            // Add the filter to G graph
            G[point].filter = Pf[i].filter;

            // Copy neighbors from Gf to G
            // Find the matching node of neighbor (from small dataset to large)
            vector<edge> gf_neighbors = Gf[j];
            vector<edge> g_neighbors;           // Vector to keep the real neighbors
            for(size_t t = 0; t < gf_neighbors.size(); t++){

                for (const auto& pair : pf_mapping){
                    if (pair.first == gf_neighbors[t].first){

                        int real_neighbor = pair.second;
                        float dist = gf_neighbors[t].second;
                        g_neighbors.push_back(make_pair(real_neighbor,dist));

                        break;
                    }
                }
            }

            // Add the real neighbors to G graph
            G[point].neighbors = g_neighbors;        
        }
    }


    // For every start node add some extra neighbors (chosen from other start nodes)
    int stf_size = STf.size();
    for(int i = 0; i < stf_size; i++){

        // Choose R_stitched random start nodes (except it self)
        vector<int> randomNeighbors = choose_N_random_nodes(R_stitched, 0, stf_size-1, i);

        int node = STf[i].start_node;
        for (int j = 0; j < R_stitched; ++j){

            int selected_neighbor = STf[randomNeighbors[j]].start_node;

            float distance = 0.0;   // For Euclidean distance

            // Calculate euclidean distance between the i node and the neighbor
            distance = EuclideanDistance(nodes[node], nodes[selected_neighbor]);

            // Add neighbor and distance
            G[node].neighbors.emplace_back(selected_neighbor, distance);
        }
    }

    return G;
}