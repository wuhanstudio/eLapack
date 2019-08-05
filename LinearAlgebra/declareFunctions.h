/*
 * declareFunctions.h
 *
 *  Created on: 8 feb. 2019
 *      Author: dell
 */

#ifndef LINEARALGEBRA_DECLAREFUNCTIONS_H_
#define LINEARALGEBRA_DECLAREFUNCTIONS_H_

//
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>


/*
 * Lapack library
 */
#include "../Lapack/Include/f2c.h"
// #include "../../src/Lapack/Include/blaswrap.h" // No need in this project! :)
#include "../Lapack/Include/clapack.h"



/*
 * Linear algebra package
 */
void tran(double* A, int row, int column);
void print(double* A, int row, int column);
void linsolve(double* A, double* X, double* B, int row, int column_b);
void svd(double* A, double* U, double* S, double* V, int row, int column);
void diag(double* A, double* B, int row_b, int column_b);
void qr(double* A, double* Q, double* R, int row, int column);
void triu(double* A, double* B, int shift, int row, int column);
void eye(double* A, int row, int column);
void mul(double* A, double* B, bool elementWise, double* C, int row_a, int column_a, int column_b);
void scale(double* A, double scalar, int row, int column);
void sub(double* A, double* B, double* C, int row_a, int column_a, int column_b);
void lu(double* A, double* L, double* U, double* P, int row, int column);
void tril(double* A, double* B, int shift, int row, int column);
void inv(double* A, int row);
void chol(double* A, double* L, int row);
double det(double *A, int row);
void toeplitz(double* A, double* B, int length);
void hankel(double* A, double* H, int length, int step);
void cut(double* A, int row, int column, double* B, int start_row, int stop_row, int start_column, int stop_column);
void diagpower(double* A, double p, int row, int column);
void eabs(double* A, int row, int column);
void add(double* A, double* B, double* C, int row_a, int column_a, int column_b);
void matcopy(double* A, double* B, int row, int column);
void cofact(double* A, double* CO, int row, int column);
void mdiag(double* A, double* B, int row, int column);
double dot(double* A, double* B, int row);
void horzcat(double* A, double* B, double* C, int row_a, int column_a, int column_b);
void maxvector(double* A, int row, double* val, int* index);
void minvector(double* A, int row, double* val, int* index);
double norm(double* A, int row, char* P);
void ones(double* A, int row, int column);
void pinv(double* A, int row, int column);
void power(double* A, int row, int column, double value);
void repmat(double* A, int row, int column, int horz, int vert, double* B);
void sqrte(double* A, int row, int column);
void sumrows(double* A, double* B, int row, int column);
void vec(double* A, double* B, int row, int column);
void vertcat(double* A, double* B, double* C, int row_a, int column_a, int row_b);
void zeros(double* A, int row, int column);
int rank(double* A, int row);
void eig(double* A, double* Ereal, double* Eimag, double* Vreal_left, double* Vimag_left, double* Vreal_right, double* Vimag_right, int row);
void mpower(double* A, int row, int n);
void insert(double* A, double* B, int row_a, int column_a, int column_b, int startRow_b, int startColumn_b);
void move(double* A, int row, int column, int down, int right);

#endif /* LINEARALGEBRA_DECLAREFUNCTIONS_H_ */
