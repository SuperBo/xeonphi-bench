CC = icc
CXX = icpc
CFLAGS = -mmic -O3
CXXFLAGS = -mmic -O3
INC = -I./
WITH_OMP = -qopenmp
WITH_TBB = -std=c++11 -ltbb
TASKSIZE = -D SIZE=42
ARRSIZE = -D SIZE=1000000

all: map reduce fib

map: map_cilk map_tbb map_openmp

reduce: reduce_cilk reduce_tbb reduce_openmp

fib: fib_cilk fib_tbb fib_openmp

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
	$(CC) $(CFLAGS) $(WITH_OMP) $(INC) $(TASKSIZE) -o bin/fib_openmp OpenMP/fib_openmp.c build/util.o

reduce_openmp: util OpenMP/reduce_openmp.c
	$(CC) $(CFLAGS) $(WITH_OMP) $(INC) $(ARRSIZE) -o bin/reduce_openmp OpenMP/reduce_openmp.c build/util.o

map_openmp: util OpenMP/map_openmp.c
	$(CC) $(CFLAGS) $(WITH_OMP) $(INC) $(ARRSIZE) -o bin/map_openmp OpenMP/map_openmp.c build/util.o

fib_tbb: util TBB/fib_tbb.cpp
	$(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(TASKSIZE) -o bin/fib_tbb TBB/fib_tbb.cpp build/util_cpp.o

map_tbb: util TBB/map_tbb.cpp
	$(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(ARRSIZE) -o bin/map_tbb TBB/map_tbb.cpp build/util_cpp.o

reduce_tbb: util TBB/reduce_tbb.cpp
	$(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(ARRSIZE) -o bin/reduce_tbb TBB/reduce_tbb.cpp build/util_cpp.o

clean:
	rm -rf build/*.o
	rm -rf bin/*
