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


// Function to print graph G (created from Filtered or Stitched Vamana)
void PrintGraph(const vector<graph> &G){

    for (size_t i = 0; i < G.size(); ++i){
        cout << endl;
        cout << "Node " << i << ":\n";
        cout << "  Filter: " << G[i].filter << "\n";
        cout << "  Neighbors: ";
        
        for (const auto& neighbor : G[i].neighbors) {
            cout << "(" << neighbor.first << ", " << neighbor.second <<")"<< " ";
        }
        cout <<endl;
    }
}


// Function to print phases of main program
void PrintPhases(){

    cout << "Available phases and arguments:" << endl;
    cout << "       groundtruth <data_path> <query_path> <groundtruth_path>" << endl;
    cout << "       filtered <data_path> <a> <L> <R>" << endl;
    cout << "       stitched <data_path> <a> <L_small> <R_small> <R_stitched>" << endl;
    cout << "       greedy <data_path> <query_path> <groundtruth_path> <L> <k> <Graph.bin_path>" << endl;
}