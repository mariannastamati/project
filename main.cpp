#include <iostream>
#include <vector>
#include <iomanip>

#include "readfiles.h"
#include "VamanaIndexing.h"

#include <cstdlib> 


int main(){
    
    // Reading input files
    string filename = "../datasets/siftsmall/siftsmall_base.fvecs";
    vector<vector<float>> vectors = read_fvecs(filename);

    // Vamana Indexing Algorithm (Creation of Vamana Graph)
    vector<vector<edge>> VamanaGraph = VamanaIndexing(vectors, vectors.size(), 500);

    return 0;

}
