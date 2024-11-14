#include "print.h"


void PrintData(vector<vector<float>> &data){

    for (size_t i = 0; i < data.size(); ++i){  
       cout << "Vector " << i << ": ";          // Print which row we are printing

        for (size_t j = 0; j < data[i].size(); ++j) {  
            cout << data[i][j] << " ";          // Print each element 
        }
        cout << endl;
    }
}