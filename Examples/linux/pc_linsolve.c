#include <stdio.h>
#include <time.h>
#include <LinearAlgebra/declareFunctions.h>

/* Matlab Code */
/* Matlab Code */
// A = [3,  4, 1; 
//      6, 10, 2; 
//      5,  3, 2]

// B = [4, 3, 22, 5; 
//      5, 3,  2, 5; 
//      3, 4,  5, 3]

// X = linsolve(A, B)

int main(int argc, char const *argv[])
{
    // Start
    clock_t start, end;
    float cpu_time_used;
    start = clock();

     // Math
    double A[3*3] = {3,  4, 1,
                     6, 10, 2,
                     5,  3, 2};

    double X[3*4];

    double B[3*4] = {4, 3, 22, 5,
                     5, 3,  2, 5,
                     3, 4,  5, 3};

    linsolve(A, X, B, 3, 4); // 3 = A row, 4 = B column
    printf("\nA = \n\n");
    print(A, 3, 3);
    printf("B = \n\n");
    print(B, 3, 4);
    printf("X = \n\n");
    print(X, 3, 4);

    // End
    end = clock();
    cpu_time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
    printf("Total speed was %f ms\n", cpu_time_used * 1000);

     return 0;
}
