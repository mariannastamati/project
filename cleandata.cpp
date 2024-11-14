#include "cleandata.h"


// Function to remove timestamps from data
void CleanData(vector<vector<float>> &data){

    for (size_t i = 0; i < data.size(); ++i) {
   
        data[i].erase(data[i].begin() + 1);  // Remove second element (Timestamp)
    }
}


// Function to remove queries related with timestamps (remove query_type 2 and 3)
void CleanQueries(vector<vector<float>>& data){
   
    for(auto it = data.begin(); it != data.end();){

        // Check if the first element is greater than 1 (means query_type is 2 or 3)
        if(!it->empty() && it->front() > 1){
            
            it = data.erase(it);        // Delete unwanted query
        }else{
            ++it;       // Else move to the next vector
        }
    }

    for (size_t i = 0; i < data.size(); ++i){
   
        data[i].erase(data[i].begin() + 2);  // Remove third element -l (special num for Timestamps)
        data[i].erase(data[i].begin() + 2);  // Remove fourth element -r (special num for Timestamps)
    }
}