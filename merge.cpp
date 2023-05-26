#include "merge.hpp"

// init the barrier
MergeSort :: MergeSort(int num_of_threads){
    NUM_THREADS = num_of_threads;
}
//destroy the barrier
MergeSort :: ~MergeSort(){
}

// other merge function that i used for lab 0  works with continuous memory vector
// doesn't work for merging two vectors
// used this function to do final merging of vectors
// same concept as Merge function underneath this
vector <int> MergeSort :: FinalMerging(vector <int> vectorA, vector <int> vectorB) {

    // vectorC is the output vector
    // it will store the merged vector obtained by merging v1 and v2
    vector<int> vectorC;
    int i = 0;
    int j = 0;
    int n, m;
    i = j = 0;
    n = vectorA.size();
    m = vectorB.size();

    // traverse each element of vectorA and vectorB
    while (i < n && j < m) {

        // merge two parts into vectorC
        if (vectorA[i] <= vectorB[j]) {
            vectorC.push_back(vectorA[i]);
            ++i;
        }
        else {
            vectorC.push_back(vectorB[j]);
            ++j;
        }

    }
    // push the elements left
    while (i < n) {
        vectorC.push_back(vectorA[i]);
        ++i;
    }
    // push the elements left
    while (j < m) {
        vectorC.push_back(vectorB[j]);
        ++j;
    }
    // return merged vector
    return vectorC;

}

// merge function from lab 0
// has to be one vector or data with continuous memory for it to work
void MergeSort :: Merge(vector<int> &data, int start, int mid, int end) {
	
	vector<int> tmp;

	int i = start;
	int j = mid + 1;

	// merge two parts into tmp
	while (i <= mid && j <= end) {
		if (data[i] <= data[j]) {
			tmp.push_back(data[i]);
			i++;
		}
		else {
			tmp.push_back(data[j]);
			j++;
		}
	}
	// Insert all the remaining values from i to mid into tmp
	while (i <= mid) {
		tmp.push_back(data[i]);
		i++;
	}
	// Insert all the remaining values from j to end into tmp
	while (j <= end) {
		tmp.push_back(data[j]);
		j++;
	}
	// Assign sorted data stored in tmp to data vector
	i = start;
	while(i <= end){
		data[i] = tmp[i-start];
		i++;
	}

}

// merge sort algorithm from lab 0
// recursively splits data and then merges
void MergeSort :: MergeSort_alg(vector<int> &data, int start, int end){
    if (start < end){
        int mid = (start + end)/2;
        MergeSort_alg(data, start, mid);
        MergeSort_alg(data, mid+1, end);
        Merge(data, start, mid, end);
    }
}

// have each thread call this function
void MergeSort :: ForkedSorting(int tid) {
    
    // master thread get startime 
    #pragma omp master
    {
        clock_gettime(CLOCK_MONOTONIC, &startTime);
    }

    // call merge sort algorithm with data that has been split
    // for that thread
	MergeSort_alg(split_data[tid],0, split_data[tid].size()-1);
    // master thread get endTime
    #pragma omp master
    {
        clock_gettime(CLOCK_MONOTONIC, &endTime);
    }
}

// split data into n number of chunks, n = number of threads
void MergeSort :: DataSplit(vector <int> &data, 
                            int size_to_split, int number_of_threads){
    // split initially from 0 to size we are splitting
    int ending_index = size_to_split;
    int starting_index = 0;

    // for the number of threads
    for(int i = 0; i < number_of_threads;i++){
        // handle last remainding chunk of data
        // doesn't always split evenly
        if( i == number_of_threads - 1){
            //get partial vector from data from starting index to end of data
            vector<int> chunk(data.begin() + starting_index,  data.end());
            // push data into our vector of vectors
            split_data.push_back(chunk);
        }
        else{
            //get partial vector from data from starting index to ending index
            vector<int> chunk(data.begin()+starting_index,data.begin()+ending_index );
            // push data into our vector of vectors
            split_data.push_back(chunk);
        }

        //move starting index to our ending index
        starting_index = ending_index;
        // move ending index the size we are splitting
        ending_index += size_to_split;

    }
}

void MergeSort :: MainDriver(vector <int> &data) {

    // get size we want to split data
    int size_to_split = round(data.size() / NUM_THREADS);

    // split the data into the number of threads we have
    DataSplit(data, size_to_split, NUM_THREADS);

    // parallelize this section with NUM_THREADS
    # pragma omp parallel num_threads(NUM_THREADS)
    {
        // get thread id 
        int tid = omp_get_thread_num();
        ForkedSorting(tid);
        #pragma omp barrier
    }
    // merge sorted vector data into one
    for(int i = 1; i < NUM_THREADS; i++) {
        split_data[0] = FinalMerging(split_data[0], split_data[i]);
    }

    // set to data
    data = split_data[0];

    //copied from example, get time
	unsigned long long elapsed_ns;
	elapsed_ns = (endTime.tv_sec-startTime.tv_sec)*1000000000 + (endTime.tv_nsec-startTime.tv_nsec);
	printf("Elapsed (ns): %llu\n",elapsed_ns);
	double elapsed_s = ((double)elapsed_ns)/1000000000.0;
	printf("Elapsed (s): %lf\n",elapsed_s);

}