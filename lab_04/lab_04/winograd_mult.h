#ifndef WINOGRAD_MULT_H
#define WINOGRAD_MULT_H

#include "matrix.h"

matrix_t winograd_mult(matrix_t a, matrix_t b, int m, int n, int q);

#endif // WINOGRAD_MULT_H