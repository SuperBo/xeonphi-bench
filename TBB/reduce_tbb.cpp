#include <iostream>

#include <tbb/tbb.h>
#include <tbb/parallel_reduce.h>
#include <tbb/task_scheduler_init.h>

#include "util.h"

using namespace tbb;

#ifndef SIZE
#define SIZE 100000
#endif

int main(int argc, char* argv[]) {
    float *a;
    float sum = 0.f;
    double run_time;

    a = (float*) _mm_malloc(SIZE * sizeof(float), 64);

    for (int i = 0; i < SIZE; i++) {
        a[i] = (i + 3) % 1000;
    }

    #ifdef NTHREADS
    task_scheduler_init init(NTHREADS);
    #else
    task_scheduler_init init(tbb::task_scheduler_init::automatic);
    #endif

    run_time = gettime();
    
    sum = parallel_reduce(
        blocked_range<size_t>(0, SIZE),
        0.f,
        [&] (const blocked_range<size_t>& range, float value) -> float {
            for (size_t i = range.begin(); i != range.end(); i++) {
                value += a[i];
            }
            return value;
        },
        [] (float x, float y) -> float {
            return x + y;
        }
    );

    run_time = gettime() - run_time;

    std::cout << "Problem size: " << SIZE << std::endl;
    std::cout << "Result sum = " << sum << std::endl;
    std::cout << "Running time: " << run_time * 1e3 << "ms" << std::endl;

    // Free
    _mm_free(a);

    return 0;
}
