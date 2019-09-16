#include <time.h>
#include "LinearAlgebra/declareFunctions.h"

/* Matlab Code */
// A = [ 4,  3,   1,  4,  2, 23;
//       6,  3,  -2,  3,  5,  8;
//       1,  3,   6,  2,  3,  2;
//       2,  5,   6,  7,  4,  4;
//       4,  6, -88,  6,  4,  6;
//       2,  1,  44, 54,  3,  2];

// [V,D, W] = eig(A)

int main( ) 
{
    clock_t start, end;
    float cpu_time_used;
    start = clock();

    // Need to be square
    double A[6*6] = { 4,  3,   1,  4,  2, 23,
                      6,  3,  -2,  3,  5,  8,
                      1,  3,   6,  2,  3,  2,
                      2,  5,   6,  7,  4,  4,
                      4,  6, -88,  6,  4,  6,
                      2,  1,  44, 54,  3,  2};


    double Ereal[6]; // Eigenvalues real
    double Eimag[6]; // Eigenvalues imag part
    double Vreal_left[6*6]; // Eigenvectors real left
    double Vimag_left[6*6]; // Eigenvectors imag left
    double Vreal_right[6*6]; // Eigenvectors real right
    double Vimag_right[6*6]; // Eigenvectors imag right

    // Solve
    eig(A,Ereal,Eimag,Vreal_left,Vimag_left,Vreal_right,Vimag_right,6);

    // Print
    printf("\nA = \n\n");
    print(A, 6, 6);
    printf("D = \n\n");
    print(Ereal, 6, 1);
    printf("Di = \n\n");
    print(Eimag, 6, 1);
    printf("W = \n\n");
    print(Vreal_left, 6, 6);
    printf("Wi = \n\n");
    print(Vimag_left, 6, 6);
    printf("V = \n\n");
    print(Vreal_right, 6, 6);
    printf("Vi = \n\n");
    print(Vimag_right, 6, 6);

    end = clock();
    cpu_time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
    printf("Total speed was %f ms\n", cpu_time_used * 1000);

    return 0;
}
