#ifndef TESTS_H
#define TESTS_H

#include <windows.h>
#include <time.h>
#include <locale.h>

#include "standart_mult.h"
#include "winograd_mult.h"

void run_tests();
void test_time(matrix_t(*f)(matrix_t, matrix_t, int, int, int), int n);

#endif // TESTS_H
