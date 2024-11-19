#include "medoid.h"
#include "print.h"

vector<Map> FindMedoid(vector<vector<float>> &nodes, int threshold){

    // Initialize M be an empty map
    vector<Map> M;
    
    // Vector to keep every filter f, and the ids of all points matching filter f
    vector<fnode> Pf;

    // Initialize Pf with the first filter of the dataset
    fnode first_node;
    first_node.filter = nodes[0][0];
    first_node.matching_points.push_back(0);
    Pf.push_back(first_node);


    int size = nodes.size();
    for(int i = 1; i < size; i++){

        // Check if filter already exists in Pf list
        bool found = false;
        for(auto& node : Pf){
            if (node.filter == nodes[i][0]){

                // If filter already exists just add node id to the matching points
                node.matching_points.push_back(i);
                found = true;           // Change found to True
                break;
            }
        }

        // If we have a new filter add it to Pf list
        if(!found){
            fnode new_node;
            new_node.filter = nodes[i][0];
            new_node.matching_points.push_back(i);
            Pf.push_back(new_node);
        }
    }

    // Initialize T in a zero map, T is intended as a counter
    vector<int> T(size,0);

    size = Pf.size();
    for(int i = 0; i < size; i++){

        // Vector to keep τ randomly sampled data point ids from Pf[i]
        vector<int> Rf = randompoints(Pf[i].matching_points,threshold);

        // For every ramdom choosen point in Rf, keep min as p*
        int pstar = -1;
        int minT = INT_MAX;
        int Rf_size = Rf.size();
        for(int j = 0; j < Rf_size; j++){

            if(T[Rf[j]] < minT){
                minT = T[Rf[j]];
                pstar = Rf[j];
            }
        }

        // Keep filter and start node we found
        Map m;
        m.filter = Pf[i].filter;
        m.start_node = pstar;
        M.push_back(m);

        // Increase counter of T[p*]
        T[pstar]++;
    }

    return M;
}


// Function to choose τ random points from a vector
vector<int> randompoints(vector<int> &points, int t){
    
    // Check if points in vector are less than τ
    int size = points.size();
    if(size <= t){

        return points; // If points are <= t, then choose and return all of them
    }

    // Random number generator
    random_device rd;
    mt19937 gen(rd());

    // Copy points in a temp vector
    vector<int> temp = points;

    // Suffle points
    shuffle(temp.begin(), temp.end(), gen);

    // Choose the first t points from suffled 
    vector<int> rand_points(temp.begin(), temp.begin() + t);

    return rand_points;
}


// Function to find the medoid of a dataset
int Medoid(const vector<vector<float>>& data){

    int medoid = -1;            // Variable to keep medoid
    double minsum = INFINITY;    // Variable to check for a smaller sum

    // Calculate the sum of Euclidean distance for every node of the graph with the other nodes
    int size = data.size();
    for (int i=0; i < size; i++){
        
        double sum = 0.0;

        for(int j=0; j < size; j++){
            if(i != j){   // If the nodes are not the same, calculate Euclidean distance
                
                sum = sum + EuclideanDistance(data[i],data[j]);
            }
        }

        // Check if a smaller sum is found and keep the new medoid of graph
        if(sum < minsum){

            minsum = sum;
            medoid = i;          // "i" node is the medoid
        }
    }
    cout << "Medoid of the Dataset: " << medoid << endl;
    return medoid;
}


// Function to find a start node from given filter
int findStartNodeFromFilter(vector<Map> STf, float filter){

    int size = STf.size();
    for(int i = 0; i < size; i++){

        if(STf[i].filter == filter){
            return STf[i].start_node;
        }
    }

    return -1;
}
