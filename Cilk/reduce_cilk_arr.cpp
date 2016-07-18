#include <iostream>

#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>

#include "util.h"

#ifndef SIZE
#define SIZE 100000
#endif

#define TILE 16384

int main(int argc, char** argv) {
    float *a;
    float result;
    double run_time;

    a = (float*) _mm_malloc(sizeof(float) * SIZE, 64);

    for (size_t i = 0; i < SIZE; i++) {
        a[i] = (i % 1000);
    }

    //cilk::reducer< cilk::op_add<float> > sum(0.f);

    // Start time
    run_time = gettime();

    __assume_aligned(a, 64);
    result = __sec_reduce_add(a[0:SIZE]);
    
    // Stop time
    run_time = gettime() - run_time;

    std::cout << "Problem size: " << SIZE << std::endl;
    std::cout << "The total sum is: " << result << std::endl;
    std::cout << "Running time is: " << run_time * 1e3 << "ms" << std::endl;

    // Free
    _mm_free(a);

    return 0;
}
