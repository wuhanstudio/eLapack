#include <rtthread.h>
#include <stdio.h>
#include <time.h>
#include <LinearAlgebra/declareFunctions.h>

/* Matlab Code */
// A = [0.674878,   0.151285,   0.875139,   0.150518;
//      0.828102,   0.150747,   0.934674,   0.474325;
//      0.476510,   0.914686,   0.740681,   0.060455;
//      0.792594,   0.471488,   0.529343,   0.743405;
//      0.084739,   0.475160,   0.419307,   0.628999;
//      0.674878,   0.151285,   0.875139,   0.150518]

// [Q, R] = qr(A)

static void elapack_qr(int argc, char const *argv[])
{
    clock_t start, end;
    float cpu_time_used;
    start = clock();

     // A matrix with size 6 x 4
    double A[6*4] = {0.674878,   0.151285,   0.875139,   0.150518,
                     0.828102,   0.150747,   0.934674,   0.474325,
                     0.476510,   0.914686,   0.740681,   0.060455,
                     0.792594,   0.471488,   0.529343,   0.743405,
                     0.084739,   0.475160,   0.419307,   0.628999,
                     0.674878,   0.151285,   0.875139,   0.150518};

    double Q[6*6];
    double R[6*4];

    // Solve
    qr(A, Q, R, 6, 4);

    // Print
    print(A, 6,4);
    print(Q, 6,6);
    print(R, 6,4);

    end = clock();
    cpu_time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTotal speed  was %f ms\n", cpu_time_used * 1000);
}
MSH_CMD_EXPORT(elapack_qr, elapack qr decomposition example);
