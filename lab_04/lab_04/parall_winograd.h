#ifndef PARALL_WINOGRAD_H
#define PARALL_WINOGRAD_H

#include <vector>
#include <thread>
#include <mutex>

#include "matrix.h"

matrix_t parall_winograd_mult_1(matrix_t a, matrix_t b, int m, int n, int q, int num_thread);
matrix_t parall_winograd_mult_2(matrix_t a, matrix_t b, int m, int n, int q, int num_thread);

#endif // PARALL_WINOGRAD_H