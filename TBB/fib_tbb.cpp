#include <iostream>
#include <tbb/tbb.h>
#include <tbb/task_group.h>

using namespace tbb;

#ifndef N
#define N 1000
#endif

int main(int argc, char* argv[]) {
    double result;

    double run_time = gettime();

    result = fib(N);

    run_time = gettime() - run_time;

    std::cout << "Result is: " << result << std::endl;
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
