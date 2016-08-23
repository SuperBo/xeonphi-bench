CC = icc
CXX = icpc
CFLAGS = -mmic -O2
CFLAGS_OFFLOAD = -O2
CXXFLAGS = -mmic -O2
INC = -I./
WITH_OMP = -qopenmp
WITH_TBB = -std=c++11 -ltbb
TASK_SIZE_L = -D SIZE=42
TASK_SIZE_M = -D SIZE=30
ARR_SIZE_S = -D SIZE=1000000
ARR_SIZE_M = -D SIZE=100000000
ARR_SIZE_L = -D SIZE=1000000000

all: map reduce fib

map: map_cilk_all map_tbb map_openmp

reduce: reduce_cilk_all reduce_tbb reduce_openmp

fib: fib_cilk fib_tbb fib_openmp

util: util.c
	$(CC) $(CFLAGS) -c -o build/util.o util.c
	$(CXX) $(CXXFLAGS) -c -o build/util_cpp.o util.c

fib_cilk: util Cilk/fib_cilk.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(TASK_SIZE_M) -o bin/fib_cilk_medium Cilk/fib_cilk.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(INC) $(TASK_SIZE_L) -o bin/fib_cilk_large Cilk/fib_cilk.cpp build/util_cpp.o

reduce_cilk_all: reduce_cilk reduce_cilk_arr reduce_cilk_tile

reduce_cilk: util Cilk/reduce_cilk.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_S) -o bin/reduce_cilk_small Cilk/reduce_cilk.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_M) -o bin/reduce_cilk_medium Cilk/reduce_cilk.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_L) -o bin/reduce_cilk_large Cilk/reduce_cilk.cpp build/util_cpp.o

reduce_cilk_arr: util Cilk/reduce_cilk_arr.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_S) -o bin/reduce_cilk_arr_small Cilk/reduce_cilk_arr.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_M) -o bin/reduce_cilk_arr_medium Cilk/reduce_cilk_arr.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_L) -o bin/reduce_cilk_arr_large Cilk/reduce_cilk_arr.cpp build/util_cpp.o

reduce_cilk_tile: util Cilk/reduce_cilk_tile.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_S) -o bin/reduce_cilk_tile_small Cilk/reduce_cilk_tile.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_M) -o bin/reduce_cilk_tile_medium Cilk/reduce_cilk_tile.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_L) -o bin/reduce_cilk_tile_large Cilk/reduce_cilk_tile.cpp build/util_cpp.o

map_cilk_all: map_cilk map_cilk_tile map_cilk_arr

map_cilk: util Cilk/map_cilk.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_S) -o bin/map_cilk_small Cilk/map_cilk.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_M) -o bin/map_cilk_medium Cilk/map_cilk.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_L) -o bin/map_cilk_large Cilk/map_cilk.cpp build/util_cpp.o

map_cilk_arr: util Cilk/map_cilk_arr.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_S) -o bin/map_cilk_arr_small Cilk/map_cilk_arr.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_M) -o bin/map_cilk_arr_medium Cilk/map_cilk_arr.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_L) -o bin/map_cilk_arr_large Cilk/map_cilk_arr.cpp build/util_cpp.o

map_cilk_tile: util Cilk/map_cilk_tile.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_S) -o bin/map_cilk_tile_small Cilk/map_cilk_tile.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_M) -o bin/map_cilk_tile_medium Cilk/map_cilk_tile.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(INC) $(ARR_SIZE_L) -o bin/map_cilk_tile_large Cilk/map_cilk_tile.cpp build/util_cpp.o

fib_openmp: util OpenMP/fib_openmp.c
	$(CC) $(CFLAGS) $(WITH_OMP) $(INC) $(TASK_SIZE_M) -o bin/fib_openmp_medium OpenMP/fib_openmp.c build/util.o
	$(CC) $(CFLAGS) $(WITH_OMP) $(INC) $(TASK_SIZE_L) -o bin/fib_openmp_large OpenMP/fib_openmp.c build/util.o

reduce_openmp: util OpenMP/reduce_openmp.c
	$(CC) $(CFLAGS) $(WITH_OMP) $(INC) $(ARR_SIZE_S) -o bin/reduce_openmp_small OpenMP/reduce_openmp.c build/util.o
	$(CC) $(CFLAGS) $(WITH_OMP) $(INC) $(ARR_SIZE_M) -o bin/reduce_openmp_medium OpenMP/reduce_openmp.c build/util.o
	$(CC) $(CFLAGS) $(WITH_OMP) $(INC) $(ARR_SIZE_L) -o bin/reduce_openmp_large OpenMP/reduce_openmp.c build/util.o

map_openmp: util OpenMP/map_openmp.c
	$(CC) $(CFLAGS) $(WITH_OMP) $(INC) $(ARR_SIZE_S) -o bin/map_openmp_small OpenMP/map_openmp.c build/util.o
	$(CC) $(CFLAGS) $(WITH_OMP) $(INC) $(ARR_SIZE_M) -o bin/map_openmp_medium OpenMP/map_openmp.c build/util.o
	$(CC) $(CFLAGS) $(WITH_OMP) $(INC) $(ARR_SIZE_L) -o bin/map_openmp_large OpenMP/map_openmp.c build/util.o

fib_tbb: util TBB/fib_tbb.cpp
	$(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(TASK_SIZE_M) -o bin/fib_tbb_auto_medium TBB/fib_tbb.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(TASK_SIZE_L) -o bin/fib_tbb_auto_large TBB/fib_tbb.cpp build/util_cpp.o
	#$(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(TASK_SIZE_) -DNTHREADS=61 -o bin/fib_tbb_61 TBB/fib_tbb.cpp build/util_cpp.o
	#$(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(TASK_SIZE_) -DNTHREADS=122 -o bin/fib_tbb_122 TBB/fib_tbb.cpp build/util_cpp.o
	#$(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(TASK_SIZE_) -DNTHREADS=244 -o bin/fib_tbb_244 TBB/fib_tbb.cpp build/util_cpp.o

map_tbb: util TBB/map_tbb.cpp
	$(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(ARR_SIZE_S) -o bin/map_tbb_auto_small TBB/map_tbb.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(ARR_SIZE_M) -o bin/map_tbb_auto_medium TBB/map_tbb.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(ARR_SIZE_L) -o bin/map_tbb_auto_large TBB/map_tbb.cpp build/util_cpp.o
	# $(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(ARR_SIZE_) -DNTHREADS=61 -o bin/map_tbb_61 TBB/map_tbb.cpp build/util_cpp.o
	# $(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(ARR_SIZE_) -DNTHREADS=122 -o bin/map_tbb_122 TBB/map_tbb.cpp build/util_cpp.o
	# $(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(ARR_SIZE_) -DNTHREADS=244 -o bin/map_tbb_244 TBB/map_tbb.cpp build/util_cpp.o

reduce_tbb: util TBB/reduce_tbb.cpp
	$(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(ARR_SIZE_S) -o bin/reduce_tbb_auto_small TBB/reduce_tbb.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(ARR_SIZE_M) -o bin/reduce_tbb_auto_medium TBB/reduce_tbb.cpp build/util_cpp.o
	$(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(ARR_SIZE_L) -o bin/reduce_tbb_auto_large TBB/reduce_tbb.cpp build/util_cpp.o
	# $(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(ARR_SIZE_) -DNTHREADS=61 -o bin/reduce_tbb_61 TBB/reduce_tbb.cpp build/util_cpp.o
	# $(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(ARR_SIZE_) -DNTHREADS=122 -o bin/reduce_tbb_122 TBB/reduce_tbb.cpp build/util_cpp.o
	# $(CXX) $(CXXFLAGS) $(WITH_TBB) $(INC) $(ARR_SIZE_) -DNTHREADS=244 -o bin/reduce_tbb_244 TBB/reduce_tbb.cpp build/util_cpp.o

fib_offload_openmp: Offload/fib_offload_openmp.c
	$(CC) $(CFLAGS_OFFLOAD) $(WITH_OMP) $(INC) $(TASK_SIZE_L) -o bin/fib_offload_openmp Offload/fib_offload_openmp.c util.c

clean:
	rm -rf build/*.o
	rm -rf bin/*
