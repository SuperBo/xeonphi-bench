#include <iostream>
#include <cilk/cilk.h>

#include "util.h"

#ifndef SIZE
#define SIZE 100
#endif

double fib(int);

int main(int argc, char** argv) {
    std::cout << "Problem size " << SIZE << std::endl;

    // Start time
    double run_time = gettime();

    double result = fib(SIZE);

    // Stop time
    run_time = gettime() - run_time;

    std::cout << "Fib(" << SIZE << ") = " << result << std::endl;
    std::cout << "Running time: " << run_time << " s" << std::endl;

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
