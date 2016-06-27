#include <iostream>
#include <tbb/tbb.h>
#include <tbb/task_group.h>

#include "util.h"

#ifndef SIZE
#define SIZE 100
#endif

using namespace tbb;

double fib(int n);

int main(int argc, char* argv[]) {
    std::cout << "Problem size " << SIZE << std::endl;
    double result;

    double run_time = gettime();

    result = fib(SIZE);

    run_time = gettime() - run_time;

    std::cout << "Fib(" << SIZE << ") = " << result << std::endl;
    std::cout << "Running time: " << run_time << std::endl;

    return 0;
}

double fib(int n) {
    if (n < 2)
        return n;

    double n1, n2;
    task_group g;

    g.run([&] {n1 = fib(n-1);});
    g.run([&] {n2 = fib(n-2);});
    
    g.wait();

    return n1 + n2;
}
