#include "mainTools.h"


int main(int argc, char **argv){

    if (argc < 2){
        cout << "USAGE: <phase> [arguments]" << endl << endl;
        cout << "Available phases and arguments:" << endl;
        cout << "       groundtruth <data_path> <query_path> <groundtruth_path>" << endl;
        cout << "       filtered <data_path> <a> <t> <L> <R>" << endl;
        cout << "       stitched <data_path> <a> <L_small> <R_small> <R_stitched>" << endl;
        cout << "       greedy <data_path> <query_path> <groundtruth_path> <L> <k>" << endl;
        
        return 1;
    }

    // Phase we want to run
    string phase = argv[1];

    uint32_t num_data_dimensions = 102;
    uint32_t num_query_dimensions = num_data_dimensions + 2;


    if (phase == "groundtruth"){
        if (argc != 4) {
            cout << "Usage: groundtruth <data_path> <query_path> " << endl;
            return 1;
        }
        GenerateGroundtruthPhase(argv[2], argv[3], num_data_dimensions, num_query_dimensions);

    }else if (phase == "filtered"){
        if (argc != 7) {
            cout << "Usage: filtered <data_path> <a> <t> <L> <R>" << endl;
            return 1;
        }
        FilteredVamanaPhase(argv[2], atof(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), num_data_dimensions);

    }else if (phase == "stitched"){
        if (argc != 7) {
            cout << "Usage: stitched <data_path> <a> <L_small> <R_small> <R_stitched>" << endl;
            return 1;
        }
        StitchedVamanaPhase(argv[2], atof(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), num_data_dimensions);

    }else if (phase == "greedy"){
        if (argc != 7) {
            cout << "Usage: greedy <data_path> <query_path> <groundtruth_path> <L> <k>" << endl;
            return 1;
        }
        GreedySearchPhase(argv[2], argv[3], argv[4], atoi(argv[5]), atoi(argv[6]), num_data_dimensions, num_query_dimensions);

    }else{
        cout << "Unknown input: " << phase << endl << endl;

        cout << "Available phases and arguments:" << endl;
        cout << "       groundtruth <data_path> <query_path> <groundtruth_path>" << endl;
        cout << "       filtered <data_path> <a> <t> <L> <R>" << endl;
        cout << "       stitched <data_path> <a> <L_small> <R_small> <R_stitched>" << endl;
        cout << "       greedy <data_path> <query_path> <groundtruth_path> <L> <k>" << endl;

        return 1;
    }

    return 0;
}