#include <windows.h>
#include <time.h>
#include <locale.h>

#include "winograd_mult.h"
#include "parall_winograd.h"


void run_tests();
void test_time_parall(matrix_t(*f)(matrix_t, matrix_t, int, int, int, int), int n, int num_threads);
void test_time_cons(matrix_t(*f)(matrix_t, matrix_t, int, int, int), int n);
