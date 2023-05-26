# Open MP

The lab was used to familarize myself with OpenMP to parallelize code.
 
### Compilation and Execution:
The submission contain a Makefile and the project builds using a single `make` command.

`mysort [--name] [source.txt] [-o out.txt] [-t NUMTHREADS]  [--alg=<merge,quick>]`

If the `--alg` argument is not provided, you should use the algorithm you have implemented.  If an algorithm is passed which you have not implemented, (e.g. `--alg=merge` when you wrote quicksort) simply print an error message and exit.

Using the `--name` option should print your name.  Otherwise, the program should sort the source file.  The source file is a text file with a single integer on each line.  The `mysort` command should then sort all integers in the source file and print them sorted one integer per line to an output file (specified by the `-o` option). The time taken to sort the file (excluding the time for file I/O and to initially launch / finally join threads) should be printed to standard out in nanoseconds.  The `-t` option specifies the number of threads that should be used, including the master thread, to accomplish the sorting.  

### Testing:
We include a `autograde.sh` script and eight test cases, located in `autograde_tests` to testcode. To run the autograder on the provided tests, use:

`./autograde.sh`

You can add additional test cases in an additional directory.  You can generate test input files using the UNIX `shuf` (shuffle) command (see below for examples using a bash shell).  Using this input file you can compare your results with `sort` using the `cmp` command, which checks if files are equivalent. To run the autograder on your own directory, use:

`./autograde.sh ./my_own_test_directory`

## Examples

Examples of your `mysort` program's syntax
```
### print your name
./mysort --name
# prints:
Your Full Name

### Consider an unsorted file
printf "3\n2\n1\n" > 321.txt
cat 321.txt
# prints
3
2
1

### Sort the text file and print to file
./mysort 321.txt -o out.txt -t5 --alg=forkjoin
# prints time taken in nanoseconds for 5 threads on fork/join sort:
294759

cat out.txt
# prints:
1
2
3
```

Several useful shell commands for this assignment:
```
### To generate a random test file ###
# -i1-10 is the range (1 to 10)
# -n5 is the length (chose 5 numbers from the range)
# testcase.txt is the output shuffled file
shuf -i1-10 -n5 > testcase.txt

### To sort a text file with linux ###
# -n is cast each line to integers
# testcase.txt is the shuffled file
# testsoln.txt is the sorted file
sort -n testcase.txt > testsoln.txt

### To compare two text files ###
# e.g. to verify your program's correctness
# Note that line endings matter!
cmp --silent myoutput.txt testsoln.txt && echo "Same!" || echo "Different!"
```


### Ease:
I feel like using OpenMP is much simpler to use than threads. I always used the newer version of threads,
compared to the regular pthread, thread package is much simpler to use. But using OpenMp is much easier than both, 
you basically just add a comment and some parenthesis and it all works so nicely. No need to resize vectors to the size of 
threads, no need to create threads, no need to join threads, everything is done by OpenMP, it's wonderful. I just have to
put the comments in the right places. 

### Strategies:
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
