#include <iostream>
#include <cilk/cilk.h>

#include "util.h"

#define ALPHA 0.2
#define BETA 0.4

#ifndef N
#define N 100000
#endif

int main(int argc, char* argv[]) {
    double a[N];
    double b[N];
    double c[N];

    for (int i = 0; i < N; i++) {
        a[i] = 2 * i % 1000;
        b[i] = 3 * i % 1000;
    }

    // Start time
    double run_time = gettime();

    cilk_for (int i = 0; i < N; i++) {
        c[i] = ALPHA * a[i] + BETA * b[i];
    }

    // Stop time
    run_time = gettime() - run_time;

    // Print result
    std::cout << "Cilk Map Running time: " << run_time << std::endl;

    return 0;
}