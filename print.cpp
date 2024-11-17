#include "print.h"


// Function to print 2D data
void PrintData(vector<vector<float>> &data){

    for (size_t i = 0; i < data.size(); ++i){  
       cout << "Vector " << i << ": ";          // Print which row we are printing

        for (size_t j = 0; j < data[i].size(); ++j) {  
            cout << data[i][j] << " ";          // Print each element 
        }
        cout << endl;
    }
}


// Function to print Medoid Map
void PrintMedoidMap(vector<Map> &M){

    for(size_t i = 0; i < M.size(); ++i){
        
        cout << "Map " << i << ": ";
        cout << "{filter: " << M[i].filter << ", start_node: " << M[i].start_node << "}" << endl;
    }
}