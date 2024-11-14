#ifndef CLEANDATA_H
#define CLEANDATA_H

#include <iostream>
#include <vector>

using namespace std;

// Function to remove unwanted elements from data (remove Timestamps)
void CleanData(vector<vector<float>> &data);

// Function to remove queries related with timestamps (remove query_type 2 and 3)
void CleanQueries(vector<vector<float>>& data);

#endif