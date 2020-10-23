#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <algorithm>
#include <Windows.h>

#include "bubble_sort.h"
#include "insert_sort.h"
#include "lsd_sort.h"

void run_tests();
void test_time(void(*f)(array_t&, int), int n);

#endif // TESTS_H
