# Sebastian Torres - CSCI 4313 (Lab 3)

### Ease:
I feel like using OpenMP is much simpler to use than threads. I always used the newer version of threads,
compared to the regular pthread, thread package is much simpler to use. But using OpenMp is much easier than both, 
you basically just add a comment and some parenthesis and it all works so nicely. No need to resize vectors to the size of 
threads, no need to create threads, no need to join threads, everything is done by OpenMP, it's wonderful. I just have to
put the comments in the right places. 

### Strategies:
My strategies for this lab were the same as lab 1. Most of the code is pulled from my lab 1.Split the data 
by the number of threads we were going to use and have each thread sort

I decided to do Merge Sort as my sorting algorithm. I split the data into chunks and had each
thread call MergeSort on its chunk. That way each individual chunk is sorted. I later joined 
their vectors into a main vector. 

### Performance Difference:
There's a significant difference between OpenMP vs threads. Pulling directly from my runs in github because I feel
like those are more consistent. Threads took 78705ns to sort the small 10in0-20 files while OpenMP only took
400ns. That is a massive difference. For the large 550000in1-1000000skew files threads took .953038 seconds, while OpenMP
only 0.051800, 18 times better which is a massive improvement.

### Organization:
    main.cpp - main driver file
    read_write.*pp - files holding functions to read and write data
    merge,*pp - files holding my functions for merge sort
    Makefile - make file to get one executable
    Examples folder - holds fix and class examples
    test.sh - extra test file 

### File Description:
main.cpp -  main driver file, gathers info from command line and calls appropriate algo with the number of threads
specified. First reads from source file, puts data into a vector, calls algo, writes vector to
output file. A lot of reused code from lab 1.

merge.hpp - header file for merge.cpp, creates MergeSort class

merge.cpp - Merge sort algorithm lives here. We have a main driver function which calls our function to split
our data n times depending on number of threads,with OpenMP then I parallelized the mergesort section.
Each thread then merge sorts on their own data chunk,they come back and join together, and the data chunks get
merged into one vector that gets written to our output file. A lot of reused code from lab 1.

read_write.hpp -  header file for read_write.cpp

read_write.cpp - same as lab 2. Has functions that read from source file and place data in a vector, also has
function to write vector back into a text file. Has usage function to print usage

### Bugs:
Currently none but its multi-threaded, so I'm sure there's one currently hiding in their.