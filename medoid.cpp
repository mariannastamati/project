#include "medoid.h"


vector<Map> FindMedoid(vector<vector<float>> &nodes, int threshold){

    // Initialize M be an empty map
    vector<Map> M;
    
    // Vector to keep every filter f, and the ids of all points matching filter f
    vector<fnode> Pf;

    // Initialize Pf with the first filter of the dataset
    fnode first_node;
    first_node.filter = nodes[0][0];
    first_node.matching_points.push_back(0);
    Pf.push_back(first_node);


    int data_size = nodes.size();
    for(int i = 1; i < data_size; i++){

        // Check if filter already exists in Pf list
        bool found = false;
        for (auto& node : Pf){
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


    return M;
}