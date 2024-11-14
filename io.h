#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <stdint.h>

#include "assert.h"

using namespace std;

// Function to read binary files (based on io.h file of GitHub repository for Sigmod Contest 2024)

// @brief Reading binary data vectors. Raw data store as a (N x dim)
// @param file_path file path of binary data
// @param data returned 2D data vectors
void ReadBin(const string &file_path, const int num_dimensions, vector<vector<float>> &data){

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