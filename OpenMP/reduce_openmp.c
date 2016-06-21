#include <stdio.h>
#include <omp.h>

#ifndef N
#define N 100000
#endif

int main(int argc, char** argv) {
    double a[N];

    double sum = 0.;
    int i;

    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        a[i] = i + 2 % 1000;
    }

    double time = gettime();

    #pragma omp parallel for private(i) reduction(+:sum)
    for (i = 0; i < N; i++) {
        sum += a[i];
    }

    time = gettime() - time;

    printf("Sum is %lf\n", sum);
    printf("Running time: %lf\n", time);

    return 0;
}
