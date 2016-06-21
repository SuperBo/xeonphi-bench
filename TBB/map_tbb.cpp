#include <iostream>
#include <tbb/tbb.h>

#include "util.h"

#ifndef N
#define N 100000
#endif

#define ALPHA 0.2
#define BETA 0.4

using namespace tbb;

int main(int argc, char* argv[]) {
    double a[N];
    double b[N];
    double c[N];

    for (int i = 0; i < N; i++) {
        a[i] = 2 * i % 1000;
        b[i] = 3 * i % 1000;
    }

    double run_time = gettime();

    parallel_for(0, N, [&] (int i) {
        c[i] = ALPHA * a[i] + BETA * b[i];
    });
    
    run_time = gettime() - run_time;

    std::cout << "TBB Map running time: " << run_time << " s" << std::endl;

    return 0;
}

