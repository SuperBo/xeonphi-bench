#include <iostream>

#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>

#include "util.h"

#ifndef SIZE
#define SIZE 100000
#endif

int main(int argc, char** argv) {
    double a[SIZE];
    double run_time;

    cilk_for (int i = 0; i < SIZE; i++) {
        a[i] = (i % 1000);
    }

    // Start time
    run_time = gettime();

    cilk::reducer< cilk::op_add<double> > sum(0);
    cilk_for (int i = 0; i < SIZE; i++) {
        *sum += a[i];
    }

    // Stop time
    run_time = gettime() - run_time;

    std::cout << "The total sum is: " << sum.get_value();
    std::cout << "Running time is: " << run_time;

    return 0;
}
