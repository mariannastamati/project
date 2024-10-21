#include <iostream>
#include <vector>
#include <iomanip>

#include "readfiles.h"
#include "VamanaIndexing.h"
#include "robustPrune.h"
#include "printGraph.h"


int main() {
    // Reading input files
    std::string filename = "../datasets/siftsmall/siftsmall_base.fvecs";
    std::vector<std::vector<float>> vectors = read_fvecs(filename);

    // Vamana Indexing Algorithm (Creation of Vamana Graph)
    std::vector<std::vector<edge>> VamanaGraph = VamanaIndexing(vectors, vectors.size(), 500);

    // Print the size of the Vamana graph (before pruning)
    std::cout << "Size of VamanaGraph (before pruning): " << VamanaGraph.size() << std::endl;
    std::cout << "Total edges before pruning: " << CountTotalEdges(VamanaGraph) << std::endl;




    // ROBUST PRUNE SECTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // Prepare inputs for RobustPrune
    int p = 0;  // The first node that the algorithm of Prune will start
    std::vector<int> V(vectors.size());
    std::iota(V.begin(), V.end(), 0);  // Fill V with all node indices
    float a = 2.0f;  // Scaling factor
    int R = 100;     // Regularity

    // Call RobustPrune
    RobustPrune(p, V, a, R, VamanaGraph);

    // Print the size of the Vamana graph (after pruning)
    std::cout << "Size of VamanaGraph (after pruning): " << VamanaGraph.size() << std::endl;
    std::cout << "Total edges after pruning: " << CountTotalEdges(VamanaGraph) << std::endl;

    return 0;
}
