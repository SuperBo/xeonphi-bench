CC=icc
CXX=icpc
CFLAGS=-mmic -openmp -O3
CXXFLAGS=-mmic -std=c++11 -O3

all:

util.o: util.c
    $(CC) -c -o build/util.o

fib_cilk: util.o fib_cilk.o
    $(CXX) -o bin/fib_cilk build/fib_cilk.o build/util.o

fib_cilk.o: Cilk/fib_cilk.cpp
    $(CXX) $(CXXFLAGS) -c -o build/fib_cilk.o Cilk/fib_cilk.cpp

reduce_cilk: util.o reduce_cilk.o
    $(CXX) -o bin/reduce_cilk build/reduce_cilk.o build/util.o

reduce_cilk.o: Cilk/map_cilk.cpp
    $(CXX) $(CXXFLAGS) -o build/reduce_cilk.o Cilk/reduce_cilk.cpp

map_cilk: util.o map_cilk.o
    $(CXX) $(CXXFLAGS) -o bin/map_cilk build/map_cilk.o buid/util.o

map_cilk.o: Cilk/map_cilk.cpp
    $(CXX) $(CXXFLAGS) -o build/map_cilk.o Cilk/map_cilk.cpp

fib_openmp: util.o fib_openmp.o
    $(CC) -o bin/fib_openmp buid/fib_openmp.o buid/util.o

fib_openmp.o: OpenMP/fib_openmp.c
    $(CC) $(CFLAGS) -o build/fib_openmp.o OpenMP/fib_openmp.c

reduce_openmp: util.o fib_openmp.o
    $(CC) -o bin/reduce_openmp build/reduce_omp.o build/util.o

reduce_openmp.o: OpenMP/reduce_openmp.c
    $(CC) $(CFLAGS) -o build/reduce_omp.o OpenMP/reduce_openmp.c

map_openmp: map_openmp.o util.o
    $(CC) $(CFLAGS) -o bin/map_openmp build/map_omp.o build/util.o

map_openmp.o: OpenMP/map_openmp.c
    $(CC) $(CFLAGS) -o build/map_omp.o OpenMP/map_openmp.c

fib_tbb: fib_tbb.o
    $(CC) $(CXXFLAGS) -o build/fib_tbb build/fib_tbb.o build/util.o

fib_tbb.o: TBB/fib_tbb.cpp
    $(CXX) $(CXXFLAGS) -o build/fib_tbb.o TBB/fib_tbb.cpp