#include <iostream>
#include <vector>
#include <iomanip>

#include "readfiles.h"

int main() {
    
    string filename = "../datasets/siftsmall/siftsmall_base.fvecs";
    vector<vector<float>> vectors = read_fvecs(filename);

    // Print vectors (keep 2 decimal)
    cout << fixed << setprecision(2);

    cout << "Read " << vectors.size() << " vectors." << endl;
    for (size_t i = 0; i < vectors.size(); ++i){

        cout << "Vector " << i + 1 << ": ";
        for (float value : vectors[i]){
            cout << value << " ";
        }

        cout << endl << endl;
    }

    return 0;
}

