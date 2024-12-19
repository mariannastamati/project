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

    // For every filter find start node (medoid)
    size = Pf.size();
    for(int i = 0; i < size; i++){

        int pf_size = Pf[i].matching_points.size();
        if(pf_size == 1){
            // Keep filter and start node we found
            Map m;
            m.filter = Pf[i].filter;
            m.start_node = Pf[i].matching_points[0];
            M.push_back(m);

            continue;
        }

        // Remove filters for Euclidean distane in Medoid calculation
        vector<vector<float>> tempnodes = nodes;
        RemoveFilters(tempnodes);

        // Save vector for every node in filter
        vector<vector<float>> pf_vector;
        for(int j = 0; j < pf_size; j++){

            int node = Pf[i].matching_points[j];
            pf_vector.push_back(tempnodes[node]);
        }

        // Call function to find real medoid of cluster
        int medoid = Medoid(pf_vector);

        // Keep filter and start node we found
        Map m;
        m.filter = Pf[i].filter;
        m.start_node = Pf[i].matching_points[medoid];
        M.push_back(m);
    }
    return M;
}


// Function to find a start node from given filter
int findStartNodeFromFilter(vector<Map> STf, float filter){

    int size = STf.size();
    for(int i = 0; i < size; i++){

        if(STf[i].filter == filter){
            return STf[i].start_node;
        }
    }

    return -1;
}


// Function to find the medoid of a Dataset
int Medoid(const vector<vector<float>>& data){

    int medoid = -1;            // Variable to keep medoid
    double minsum = INFINITY;    // Variable to check for a smaller sum

    // Calculate the sum of Euclidean distance for every node of the graph with the other nodes
    int size = data.size();
    for (int i=0; i < size; i++){
        
        double sum = 0.0;

        for(int j=0; j < size; j++){
            if(i != j){   // If the nodes are not the same, calculate Euclidean distance
                
                sum = sum + EuclideanDistance(data[i],data[j]);
            }
        }

        // Check if a smaller sum is found and keep the new medoid of graph
        if(sum < minsum){

            minsum = sum;
            medoid = i;          // "i" node is the medoid
        }
    }
    return medoid;
}