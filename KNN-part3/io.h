#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <stdint.h>
#include <sstream>

#include "assert.h"
#include "graph.h"

using namespace std;


// Function to read binary files (based on io.h file of GitHub repository for Sigmod Contest 2024)
// @brief Reading binary data vectors. Raw data store as a (N x dim)
// @param file_path file path of binary data
// @param data returned 2D data vectors
inline void ReadBin(const string &file_path, const int num_dimensions, vector<vector<float>> &data){

  ifstream ifs;
  ifs.open(file_path, std::ios::binary);
  assert(ifs.is_open());

  uint32_t N;           // num of points
  ifs.read((char *)&N, sizeof(uint32_t));
  data.resize(N);

  vector<float> buff(num_dimensions);
  int counter = 0;
  while (ifs.read((char *)buff.data(), num_dimensions * sizeof(float))){

    vector<float> row(num_dimensions);
    for (int d = 0; d < num_dimensions; d++) {
      row[d] = static_cast<float>(buff[d]);
    }

    data[counter++] = move(row);
  }

  ifs.close();
  cout << "Finish Reading" << endl;
}


// Read Groundtruth
inline vector<vector<int>> readGroundtruth(const string& filename){

    ifstream file(filename);
    vector<std::vector<int>> result;
    string line;

    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return result;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        vector<int> row;
        int number;
        bool hasNumbers = false;

        while (ss >> number) {
            row.push_back(number);
            hasNumbers = true;
        }

        // If the line is empty then write -1 in vector
        if (!hasNumbers) {
            row.push_back(-1);
        }

        result.push_back(row);
    }

    file.close();

    cout << "Finish Reading" << endl;
    return result;
}


// Save graph to file.bin
inline void saveGraphToFile(const vector<graph>& G_Stitched, const string& filename){
  
    ofstream outfile(filename, ios::binary);
    if (!outfile) {
        cerr << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the size of the graph vector
    size_t graphSize = G_Stitched.size();
    outfile.write(reinterpret_cast<const char*>(&graphSize), sizeof(graphSize));

    for (const auto& node : G_Stitched) {
        // Write the filter value
        outfile.write(reinterpret_cast<const char*>(&node.filter), sizeof(node.filter));

        // Write the size of the neighbors vector
        size_t neighborSize = node.neighbors.size();
        outfile.write(reinterpret_cast<const char*>(&neighborSize), sizeof(neighborSize));

        // Write each neighbor (pair<int, float>)
        for (const auto& [neighbor, distance] : node.neighbors) {
            outfile.write(reinterpret_cast<const char*>(&neighbor), sizeof(neighbor));
            outfile.write(reinterpret_cast<const char*>(&distance), sizeof(distance));
        }
    }

    outfile.close();
}


// Read graph.bin and return graph
inline vector<graph> ReadGraphFile(const string& filename){

    ifstream infile(filename, ios::binary);
    if (!infile) {
        cerr << "Error: Could not open file for reading." << endl;
        return {};
    }

    vector<graph> Graph;

    // Read the size of the graph vector
    size_t graphSize;
    infile.read(reinterpret_cast<char*>(&graphSize), sizeof(graphSize));
    Graph.resize(graphSize);

    for (auto& node : Graph) {
        // Read the filter value
        infile.read(reinterpret_cast<char*>(&node.filter), sizeof(node.filter));

        // Read the size of the neighbors vector
        size_t neighborSize;
        infile.read(reinterpret_cast<char*>(&neighborSize), sizeof(neighborSize));
        node.neighbors.resize(neighborSize);

        // Read each neighbor (pair<int, float>)
        for (auto& [neighbor, distance] : node.neighbors) {
            infile.read(reinterpret_cast<char*>(&neighbor), sizeof(neighbor));
            infile.read(reinterpret_cast<char*>(&distance), sizeof(distance));
        }
    }

    infile.close();
    return Graph;
}