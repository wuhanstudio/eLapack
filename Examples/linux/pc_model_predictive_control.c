#include <time.h>
#include "LinearAlgebra/declareFunctions.h"

/*
 * Here you can set the sizes for the matrices
 */

#define row_a 2 // A row
#define column_a 2 // A column

#define row_b 2 // B row, the same row as A.
#define column_b 1 // B column, the same column as D

#define row_c 1 // C row, the same row as D
#define column_c 2 // C column, the same column as A

/*
 * Create a state space model - discrete
 */
double A[row_a * column_a] = { -0.099272, 0.029481,
        -0.088444, -0.158234};

double B[row_b * column_b] = { 0.366424,
                               0.029481
};

double C[row_c * column_c] = {1, 0};

double D[row_c * column_b] = {0};

double X[row_a] = {0, 0};

double R =  6;

// Create the length of the observability matrix, notice it will have the dimension (row_o * row_c + row_c) x column_b
#define row_o 20

// Create the widt of the lower triangular toeplitz H matrix, notice that it will have the dimension (row_o * row_c + row_c) x (column_h * column_b)
#define column_h 19 // column_h < row_o - always!

// Define the column of the reference vector - Standard is 1
#define column_ry 1

int main() {

    /*
     * Model predictive control
     */

    clock_t start, end;
    float cpu_time_used;
    start = clock();

    /*
     * Create the Observabillity matrix and the
     */

    double O[(row_o * row_c) * row_a];
    double O_[(row_o * row_c) * row_a]; // This is for the lower triangular toeplitz matrix
    double A_[row_a * column_a];
    double C_[row_c * column_c];

    for (int i = 1; i <= row_o; i++) {
        matcopy(A, A_, row_a, column_a); // Copy A -> A_
        mpower(A_, row_a, i); // Power A_^i
        mul(C, A_, false, C_, row_c, column_c, column_a); // C_ = C*A_
        insert(C_, O, row_c, column_c, row_a, (i-1)*row_c, 0); // Insert O = [CA^1; CA^2; CA^3; ... ; CA^row_o];

        matcopy(A, A_, row_a, column_a); // Copy A -> A_
        mpower(A_, row_a, i - 1); // Power A_^(i-1)
        mul(C, A_, false, C_, row_c, column_c, column_a); // C_ = C*A_
        insert(C_, O_, row_c, column_c, row_a, (i-1)*row_c, 0); // Insert O_ = [CA^0; CA^1; CA^2; ... ; CA^(row_o-1)];
    }

    //print(O, row_o * row_c, row_a);

    /*
     * Create the lower triangular toeplitz matrix
     */
    double H[(row_o * row_c) * (column_h * column_b)];
    zeros(H, row_o * row_c, column_h * column_b);

    // T = O_*B - Observabillity matrix times B
    double T[(row_o * row_c) * column_b];
    mul(O_, B, false, T, row_o * row_c, row_a, column_b);


    // Lower triangular toeplitz matrix of T = [C*A^0*B; C*A^1*B; C*A^2*B; C*A^3*B; ...; C*A^(row_o-1)*B]
    for (int j = 0; j < column_h; j++){
        insert(T, H, row_o * row_c, column_b, column_h * column_b, 0, j*column_b);
        move(T, row_o * row_c, column_b, row_c , 0);
    }

    //print(H, row_o * row_c, column_h * column_b); // H matrix


    /*
     * Compute U = pinv(H)*(Ry*R - O*X), where R is our reference vector, X is our initial state vector
     */

    pinv(H, row_o * row_c, column_h * column_b); // Pseudo inverse of H. Using the SVD method

    double Ry[(row_o * row_c)*column_ry];
    ones(Ry, row_o * row_c, column_ry);
    scale(Ry, R, row_o * row_c, column_ry); // Ry*R = Ry

    double OX[(row_o * row_c)*column_ry];
    mul(O, X, false, OX, row_o * row_c, row_a, column_ry); // O*X

    double Ry_OX[(row_o * row_c)*column_ry];
    sub(Ry, OX, Ry_OX, row_o * row_c, column_ry, column_ry); // Ry-O*X

    double U[(column_h * column_b)*column_ry];
    mul(H, Ry_OX, false, U, column_h * column_b, row_o * row_c, column_ry); // U = pinv(H)*(Ry-O*X);

    /*
     * Our best input values
     */
    print(U, column_h * column_b, column_ry);


    end = clock();
    cpu_time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
    printf("Total speed  was %f ms\n", cpu_time_used * 1000);

    return 0;
}
