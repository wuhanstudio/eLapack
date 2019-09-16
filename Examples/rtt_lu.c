#include <rtthread.h>
#include <stdio.h>
#include <time.h>
#include <LinearAlgebra/declareFunctions.h>

/* Matlab Code */
// A = [2, 7, 6, 2;
//      9, 5, 1, 3;
//      4, 3, 8, 4;
//      5, 6, 7, 8;
//      2, 2, -3,-1]
// [U, L, P] = lu(A)

static void elapack_lu(int argc, char const *argv[])
{
    clock_t start, end;
    float cpu_time_used;
    start = clock();

    double A[5*4] = {2, 7, 6, 2,
                    9, 5, 1, 3,
                    4, 3, 8, 4,
                    5, 6, 7, 8,
                    2, 2, -3,-1
    };

    double U[4*4];
    double L[5*4];
    double P[5*5];

    // Solve
    lu(A, L, U, P, 5, 4);

    // Print
    print(A, 5,4);
    print(U, 4,4);
    print(L, 5,4);
    print(P, 5,5);


    end = clock();
    cpu_time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTotal speed  was %f ms\n", cpu_time_used * 1000);
}
MSH_CMD_EXPORT(elapack_lu, elapack lu decomposition example);
