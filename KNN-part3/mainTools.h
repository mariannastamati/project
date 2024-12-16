#ifndef MAINTOOLS_H
#define MAINTOOLS_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <chrono>

#include "io.h"
#include "print.h"
#include "cleandata.h"
#include "groundtruth.h"
#include "FilteredVamana.h"
#include "StitchedVamana.h"
#include "recall.h"


using namespace std;
using namespace chrono;

// Generate groundtruth Phase
void GenerateGroundtruthPhase(const string& source_path, const string& query_path,
    uint32_t num_data_dimensions, uint32_t num_query_dimensions);

// Filtered Vamana Phase
void FilteredVamanaPhase(const string& source_path, float a, int t, int L, int R, uint32_t num_data_dimensions); 

// Stitched Vamana Phase
void StitchedVamanaPhase(const string& source_path, float a, int L_small, int R_small, int R_stitched, 
    uint32_t num_data_dimensions);

// Greedy Search and Recall Phase
void GreedySearchPhase(const string& source_path, const string& query_path, const string& groundtruth_path, 
    float a, int L, int k, uint32_t num_data_dimensions, uint32_t num_query_dimensions);


#endif