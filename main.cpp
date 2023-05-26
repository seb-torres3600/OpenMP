/*
Sebastian Torres
11/7/22
Lab 3
*/

#include <iostream>
#include <unistd.h>
#include <getopt.h>
#include "read_write.hpp"
#include "merge.hpp"

using namespace std;

int main(int argc, char** argv){

    // Variable declarations
    int our_option;
    // Num of threads defaults to 4 if nothing passed
    int  NUM_THREADS = 4;
    string sorting_algo;
    // merge is default algorithm
    string alg_type = "merge";
    string outputFile;
    string sourceFile;

    // get source file
    if (argc > 2){
        sourceFile = string(argv[1]);
    }

    // Creating the long options
    static struct option long_options[] = {
            {"name",   no_argument,         0,  'n' },
            {"alg",   required_argument,   0,  'a' },
            {0, 0, 0, 0}
    };

    // get all arguments
    while(1) {
        int index = 0;
        our_option = getopt_long(argc, argv, "na:s:t:i:o:",long_options, &index);

        // When all the options have been read
        if (our_option == -1) {
            break;
        }

        switch(our_option) {

            // Name option. Program will terminate after printing name.
            case 'n': {

                cout << "Sebastian Torres" << endl;
                return 0;

            }

                // Choose alg type
            case 'a': {

                alg_type = optarg;

                if(alg_type != "merge" && alg_type != "quick"){
                    print_usage();
                    return -1;
                }
                if(alg_type == "quick"){
                    cout << "Quick sort not implemented" << endl;
                    print_usage();
                    return -1;
                }
                break;

            }

                // Number of threads
            case 't': {

                NUM_THREADS = atoi(optarg);
                if(NUM_THREADS > 150){
                    cout << "ERROR; too many threads\n" << endl;
                    return -1;
                }

                break;

            }

                // Name of outputfile
            case 'o': {

                outputFile = optarg;
                break;

            }

        }

    }

    // vector to hold data
    vector <int> data;
    // read from source file and turn into vector
    data = read_from_file(sourceFile);
    //call sorter
    MergeSort mergesort(NUM_THREADS);
    mergesort.MainDriver(data);

    // write to file
    write_to_file(outputFile, data);
    return 0;
}
