#include <iostream>

#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>

#include "util.h"

#ifndef N
#define N 100000
#endif

int main(int argc, char** argv) {
    double a[N];
    double run_time;

    cilk_for (int i = 0; i < N; i++) {
        a[i] = (i % 1000);
    }

    // Start time
    run_time = gettime();

    cilk::reducer< cilk::op_add<double> > sum(0);
    cilk_for (int i = 0; i < N; i++) {
        *sum += a[i];
    }

    // Stop time
    run_time = gettime() - run_time;

    std::cout << "The total sum is: " << sum.get_value();
    std::cout << "Running time is: " << std:setw(5) << run_time;

    return 0;
}
