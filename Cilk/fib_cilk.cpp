#include <iostream>

#include <clik/cilk.h>

#include "util.h"

#ifndef N
#define N 1000
#endif

int main(int argc, char** argv) {

    // Start time
    double run_time = gettime();

    double result = fib(N);

    // Stop time
    run_time = gettime() - run_time;

    std::cout << "The output is " << result << std::endl;
    std::cout << "Running time: " << time << " s" << std::endl;

    return 0;
}

double fib(int n) {
    if (n < 2) {
        return (double) n;
    }

    double n1 = cilk_spawn fib(n - 1);
    double n2 = fib(n - 2);

    cilk_sync;

    return n1 + n2;
}
