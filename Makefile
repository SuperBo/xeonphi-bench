CC = icc
CXX = icpc
CFLAGS = -mmic -qopenmp -O3
CXXFLAGS = -mmic -std=c++11 -ltbb -O3
INC = -I./
TASKSIZE = -D SIZE=1000
ARRSIZE = -D SIZE=1000000

all: cilk tbb openmp

cilk: fib_cilk map_cilk reduce_cilk

tbb: fib_tbb map_tbb reduce_tbb

openmp: fib_openmp map_openmp reduce_openmp

util: util.c
	$(CC) $(CFLAGS) -c -o build/util.o util.c
	$(CXX) $(CXXFLAGS) -c -o build/util_cpp.o util.c

fib_cilk: util Cilk/fib_cilk.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(TASKSIZE) -o bin/fib_cilk Cilk/fib_cilk.cpp build/util_cpp.o

reduce_cilk: util Cilk/reduce_cilk.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(ARRSIZE) -o bin/reduce_cilk Cilk/reduce_cilk.cpp build/util_cpp.o

map_cilk: util Cilk/map_cilk.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(ARRSIZE) -o bin/map_cilk Cilk/map_cilk.cpp build/util_cpp.o

fib_openmp: util OpenMP/fib_openmp.c
	$(CC) $(CFLAGS) $(INC) $(TASKSIZE) -o bin/fib_openmp OpenMP/fib_openmp.c build/util.o

reduce_openmp: util OpenMP/reduce_openmp.c
	$(CC) $(CFLAGS) $(INC) $(ARRSIZE) -o bin/reduce_openmp OpenMP/reduce_openmp.c build/util.o

map_openmp: util OpenMP/map_openmp.c
	$(CC) $(CFLAGS) $(INC) $(ARRSIZE) -o bin/map_openmp OpenMP/map_openmp.c build/util.o

fib_tbb: util TBB/fib_tbb.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(TASKSIZE) -o bin/fib_tbb TBB/fib_tbb.cpp build/util_cpp.o

map_tbb: util TBB/map_tbb.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(ARRSIZE) -o bin/map_tbb TBB/map_tbb.cpp build/util_cpp.o

reduce_tbb: util TBB/reduce_tbb.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(ARRSIZE) -o bin/reduce_tbb TBB/reduce_tbb.cpp build/util_cpp.o

clean:
	rm -rf build/*.o
	rm -rf bin/*
