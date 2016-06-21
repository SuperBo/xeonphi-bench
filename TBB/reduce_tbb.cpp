#include <iostream>

#include <tbb/tbb.h>
#include <tbb/parallel_reduce.h>

#include "util.h"

using namespace tbb;

#ifndef SIZE
#define SIZE 100000
#endif

int main(int argc, char* argv[]) {
    double a[SIZE];
    double runtime;
    double sum = 0;

    for (int i = 0; i < SIZE; i++) {
        a[i] = (i + 3) % 1000;
    }

    runtime = gettime();
    
    sum = parallel_reduce(
        blocked_range<double*>(a, a + SIZE),
        0.f,
        [] (const blocked_range<double*>& range, double value) -> double {
            for (double* b = range.begin(); b != range.end(); b++) {
                value += *b;
            }
            return value;
        },
        [] (double x, double y) -> double {
            return x + y;
        }
    );

    runtime = gettime() - runtime;

    std::cout << "Result sum = " << sum << std::endl;
    std::cout << "Running time: " << time << "s" << std::endl;

    return 0;
}
