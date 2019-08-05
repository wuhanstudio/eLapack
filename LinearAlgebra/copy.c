/*
 * copy.c
 *
 *  Created on: 15 feb. 2019
 *      Author: dell
 */

#include "declareFunctions.h"
/*
 * Copy a matrix A -> B
 */

void matcopy(double* A, double* B, int row, int column) {
	memcpy(B, A, column * row * sizeof(double));
}
