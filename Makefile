CXX = g++
CXXFLAGS = -fopenmp -O3 -std=c++2a -g -Wall -Wextra

all: main

clean:
	rm merge.o read_write.o mysort

main: read_write.o merge.o main.cpp
	$(CXX) $(CXXFLAGS) main.cpp read_write.o merge.o -o mysort

read_write.o: read_write.cpp
	$(CXX) $(CXXFLAGS) -c read_write.cpp

merge.o: merge.cpp
	$(CXX) $(CXXFLAGS) -c merge.cpp
