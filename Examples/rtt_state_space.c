#include <rtthread.h>
#include <stdio.h>
#include <time.h>
#include <LinearAlgebra/declareFunctions.h>

static void elapack_state_space(int argc, char const *argv[])
{
    /*
     * G(s) = 1/(s^2 + 1s + 3)  - Model
     * y = measured output values
     * u = measured input values
     */

    clock_t start, end;
    float cpu_time_used;
    start = clock();

    double y[144] = { 0.00000, 0.49525, 1.43863, 2.13779, 2.30516, 2.05713,
            1.69220, 1.45608, 1.42777, 1.54146, 1.67927, 1.75624, 1.75400,
            1.70478, 1.65394, 1.62996, 1.63549, 1.65594, 1.67426, 1.68125,
            1.67752, 1.66930, 1.66285, 1.66102, 1.66300, 1.66621, 1.66842,
            1.66880, 1.66786, 1.66664, 1.66591, 1.66588, 1.66629, 1.66675,
            1.66698, 1.66695, 1.66678, 1.66661, 1.66654, 1.66657, 1.66664,
            1.66670, 1.66672, 1.66670, 1.66667, 1.66665, 1.66665, 1.66666,
            1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66666, 1.66666,
            1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667,
            1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667,
            1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667,
            1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667,
            1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667,
            1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667,
            1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667,
            1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667,
            1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667,
            1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667,
            1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667,
            1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667, 1.66667,
            1.66667, 1.66667, 1.66667, 1.66667, 1.66667 };

    double u[144] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
            5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
            5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
            5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
            5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
            5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
            5, 5, 5, 5, 5, 5, 5, 5, 5 };

    // Toeplitz matrix
    double toe[144 * 144];
    toeplitz(u, toe, 144);

    // Upper triangular
    double tru[144 * 144];
    triu(toe, tru, 0, 144, 144);

    // inverse
    inv(tru, 144);

    // Multiplication
    double g[144];
    mul(y, tru, false, g, 1, 144, 144);

    // Create hankel
    double H0[144 * 144];
    hankel(g, H0, 144, 1);
    double H1[144 * 144];
    hankel(g, H1, 144, 2);

    // Cut hankel into half
    double H0_half[72 * 72];
    double H1_half[72 * 72];
    cut(H0, 144, 144, H0_half, 0, 71, 0, 71);
    cut(H1, 144, 144, H1_half, 0, 71, 0, 71);

    // Do SVD
    double U[72 * 72];
    double S[72 * 72];
    double V[72 * 72];
    svd(H0_half, U, S, V, 72, 72);

    // Model reduction to second order model
    double Un[72 * 2];
    double Sn[2 * 2];
    double Vn[72 * 2];
    cut(U, 72, 72, Un, 0, 71, 0, 1);
    cut(S, 72, 72, Sn, 0, 1, 0, 1);
    cut(V, 72, 72, Vn, 0, 71, 0, 1);

    // Create A, B, C
    double Sn_sqrt_negative[2 * 2];
    double Sn_sqrt_positive[2 * 2];
    matcopy(Sn, Sn_sqrt_negative, 2,2);
    matcopy(Sn, Sn_sqrt_positive, 2,2);
    diagpower(Sn_sqrt_negative, -0.5, 2, 2);
    diagpower(Sn_sqrt_positive, 0.5, 2, 2);

    /*
     * C = Un*Sn^(1/2);
     * Cd = C(1, 1:2)
     */
    double C[72 * 2];
    double Cd[1 * 2];
    mul(Un, Sn_sqrt_positive, false, C, 72, 2, 2);
    cut(C, 72, 2, Cd, 0, 0, 0, 1);

    /*
     * Ad = Sn^(-1/2)*Un'*H1*Vn*Sn^(-1/2);
     */
    double A[72 * 2];
    double A1[72 * 2];
    double Ad[2 * 2];
    double Ad1[2 * 2];
    mul(Vn, Sn_sqrt_negative, false, A, 72, 2, 2);
    mul(H1_half, A, false, A1, 72, 72, 2);
    tran(Un, 72, 2);
    mul(Un, A1, false, Ad1, 2, 72, 2);
    mul(Sn_sqrt_negative, Ad1, false, Ad, 2, 2, 2);

    /*
     * B = Sn^(1/2)*Vn'
     * Bd = B(:, 1);
     */
    double B[2 * 72];
    double Bd[2 * 1];
    tran(Vn, 72, 2);
    mul(Sn_sqrt_positive, Vn, false, B, 2, 2, 72);
    cut(B, 2, 72, Bd, 0, 1, 0, 0);

    /*
     * Print A, B, C
     */
    printf("A Matrix: \n");
    print(Ad, 2, 2);

    printf("B Matrix: \n");
    print(Bd, 2, 1);

    printf("C Matrix: \n");
    print(Cd, 1, 2);

    end = clock();
    cpu_time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTotal speed  was %f ms\n", cpu_time_used * 1000);
}
MSH_CMD_EXPORT(elapack_state_space, elapack state space example);
