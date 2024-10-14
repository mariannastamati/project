#include "readfiles.h"

using namespace std;

// Function to read and save .fvecs files contents
vector<vector<float>> read_fvecs(const string& filename){

    ifstream file(filename, ios::binary);  // Open file

    // Check if the file is open
    if (!file.is_open()){
        cerr << "Error: Could not open file. " << filename << endl;
        exit(1);
    }

    vector<vector<float>> data;  // Vector to save contents

    while (!file.eof()){

        int dimension = 0;  // Read the dimension of the vector
        file.read(reinterpret_cast<char*>(&dimension), sizeof(int));

        if (file.eof()) break;  // Check for end of file

        vector<float> vec(dimension);  // Create a vector to save contents
        file.read(reinterpret_cast<char*>(vec.data()), dimension * sizeof(float));  // Read contents

        data.push_back(vec);
    }

    file.close();  // Close file

    return data;
}