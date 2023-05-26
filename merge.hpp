#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <ctime>
#include <omp.h>

using namespace std;

class MergeSort{
    private:
        int NUM_THREADS;
        struct timespec startTime, endTime;
        vector<vector<int>> split_data;

    public:
        MergeSort(int num_of_threads);
        ~MergeSort();
        vector<int> FinalMerging(vector <int> vectorA, vector <int> vectorB);
        void Merge(vector<int> &data, int start, int mid, int end);
        void MergeSort_alg(vector<int> &data, int start, int end);
        void ForkedSorting(int tid);
        void DataSplit(vector <int> &data, int size_to_split, int number_of_threads);
        void MainDriver(vector <int> &data);
};