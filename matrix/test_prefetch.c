#include <omp.h>
#include <stdlib.h>

int main(int argc, char* argvs[]){
    int a [128];
    int i,j;

    #pragma prefetch a:1:16
    for (i = 0; i < 64; i++){
        a[i] = 1 + 2;
    }

    #pragma prefetch a:1:16
    for (i = 0; i < 64; i++){
        for (j = 0; j < 32; j++)
            a[i] = 2 + 2;
    }

    #pragma noprefetch a
    for (i = 0; i < 64; i++){
        a[i] = 2 + 2;
    }

    #pragma noprefetch a
    for (i = 0; i < 64; i++){
        for (j = 0; j < 32; j++)
            a[i] = 2 + 2;
    }

    return 0;
}
