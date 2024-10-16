#include <iostream>
#include <vector>
#include <iomanip>

#include "readfiles.h"
#include "VamanaIndexing.h"


int main() {
    
    // Reading input files
    string filename = "../datasets/siftsmall/siftsmall_base.fvecs";
    vector<vector<float>> vectors = read_fvecs(filename);

    // Vamana Indexing Algorithm
    VamanaIndexing(vectors, vectors.size(), 100);

    return 0;
}
