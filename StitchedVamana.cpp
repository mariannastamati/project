#include "StitchedVamana.h"

// Stitched Vamana Indexing algorithm
vector <graph> StitchedVamana(vector<vector<float>> &nodes, float a, int L_small, int R_small, int R_stitched, vector<Map> STf){

    // Initialize G to an empty graph
    vector <graph> G;

    // Vector Pf to keep every filter f, and the ids of all points matching filter f
    vector<fnode> Pf;

    // Initialize Pf with the first filter of the dataset
    fnode first_node;
    first_node.filter = nodes[0][0];
    first_node.matching_points.push_back(0);
    Pf.push_back(first_node);


    int size = nodes.size();
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
        vector<pair<int,int>> pf_mapping;         // A map to help find the wright node in the smaller dataset of filter f
        for(int j = 0; j < pfsize; j++){

            vector<float> node = temp[Pf[i].matching_points[j]];
            pf_nodes.push_back(node);

            // Match nodes from large dataset to nodes form small 
            pf_mapping.push_back(make_pair(j,Pf[i].matching_points[j]));
        }

        // Get medoid (start node of filter)
        int medoid = STf[i].start_node;

        // Create a graph for filter f nodes
        //vector<vector<edge>> g = VamanaIndexing(pf_nodes,pf_mapping,a,L_small,R_small,medoid);

    }

    return G;
}