#ifndef GROUNDTRUTH_H
#define GROUNDTRUTH_H

#include <fstream>
#include <string>

#include "graph.h"      // For Euclidean distance function
#include "medoid.h"     // For fnode struct
#include "cleandata.h"


// Function to generate Groundtruth file for queries (contains the real K nearest neighbors of every query)
inline void generateGroundTruth(vector<vector<float>> &queries, vector<vector<float>> &data, int k){

    ofstream file("groundtruth.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    // DATA FOR USE IN EUCLIDEAN DISTANCE
    vector<vector<float>> clean_d = data;
    RemoveFilters(clean_d);     // Remove filter

    vector<vector<float>> clean_q = queries;
    RemoveFilters(clean_q);     // Remove query type
    RemoveFilters(clean_q);     // Remove filter

    
    // ---------------- FOR FILTERED QUERIES ONLY ---------------- 
    // Vector Pf to keep every filter f, and the ids of all points matching filter f
    vector<fnode> Pf;

    // Initialize Pf with the first filter of the dataset
    fnode first_node;
    first_node.filter = data[0][0];
    first_node.matching_points.push_back(0);
    Pf.push_back(first_node);

    int datasize = data.size();
    for(int i = 1; i < datasize; i++){

        // Check if filter already exists in Pf list
        bool found = false;
        for(auto& node : Pf){
            if (node.filter == data[i][0]){

                // If filter already exists just add node id to the matching points
                node.matching_points.push_back(i);
                found = true;           // Change found to True
                break;
            }
        }

        // If we have a new filter add it to Pf list
        if(!found){
            fnode new_node;
            new_node.filter = data[i][0];
            new_node.matching_points.push_back(i);
            Pf.push_back(new_node);
        }
    }
    // -----------------------------------------------------------

    // For every query in queries
    int size = queries.size();
    for(int i = 0; i < size; i++){

        // If query_type = 0 (unfiltered) check for neighbors in all data points
        if(queries[i][0] == 0){

            vector<pair<int, float>> List;

            for(int j = 0 ; j < datasize; j++){

                // Calculate distance between query and every point in dataset
                float dist = EuclideanDistance(clean_q[i],clean_d[j]);

                // Add distance to the distance list
                List.push_back(make_pair(j,dist));
            }

            // Keep k nearest neighbors
            sort(List.begin(), List.end(), [](pair<int, float> a, pair<int, float> b) {return a.second < b.second;});
            List.resize(k); // We return only the k closest points

            // Write to file
            for(int j = 0; j < k; j++){
                file << List[j].first << " ";
            }
            file << endl;
        }
        

        // If query_type = 1 (filtered) check for neighbors only in points with the same filter
        if(queries[i][0] == 1){

            vector<pair<int, float>> List;

            // Find in Pf list the same filter as query
            int pfsize = Pf.size();
            bool found = 0;         // Filter not found yet
            for(int j = 0; j < pfsize; j++){

                // If filter is the same, then check for nearest neighbors only in matching nodes
                if(Pf[j].filter == queries[i][1]){

                    // Filter found, set found to 1
                    found = 1;

                    vector<int> matching_p = Pf[j].matching_points;
                    int mp_size = matching_p.size();

                    if(mp_size <= k)
                    {
                        for(int l = 0; l < mp_size; l++){
                            file << matching_p[l] << " ";
                        }
                        file << endl;
                        continue;
                    }

                    for(int l = 0; l < mp_size; l++){

                        // Calculate distance between query and every point in matching points
                        vector<float> m_point = clean_d[matching_p[l]];
                        float dist = EuclideanDistance(clean_q[i],m_point);

                        // Add distance to the distance list
                        List.push_back(make_pair(matching_p[l],dist));
                    }

                    // Keep k nearest neighbors
                    sort(List.begin(), List.end(), [](pair<int, float> a, pair<int, float> b) {return a.second < b.second;});
                    List.resize(k); // We return only the k closest points

                    // Write to file
                    for(int j = 0; j < k; j++){
                        file << List[j].first << " ";
                    }
                    file << endl;

                    break; // Found: Break and move to the next query
                }
            }

            // If filter not found write nothing (for no neighbors)
            if(found == 0){
                file << endl;
            }
        }
    }

    file.close();
}

#endif