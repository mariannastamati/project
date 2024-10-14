#ifndef READFILES_H
#define READFILES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Function to read .fvecs files
vector<vector<float>> read_fvecs(const string& filename);

#endif