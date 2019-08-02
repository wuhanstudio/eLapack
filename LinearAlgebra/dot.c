/*
 * dot.c
 *
 *  Created on: 15 feb. 2019
 *      Author: dell
 */

#include "declareFunctions.h"

/*
 * Find the dot product of two vectors A and B with the same size: row x 1
 */

double dot(double* A, double* B, int row) {

	// Reset
	double sum = 0;

	// Multiply each row
	for (int i = 0; i < row; ++i) {
		sum += (*(A + i)) * (*(B + i));
	}
	return sum;

}
