#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <memory>

#define		EPS		1e-5

using namespace std;

typedef double* array_t;

array_t create_array(int n);
array_t copy_array(array_t arr, int n);
void free_array(array_t* arr);

void fill_array(array_t arr, int n);
array_t random_fill_array(int n);

bool cmp_array(array_t arr1, array_t arr2, int n);

void print_array(array_t arr, int n);

#endif // ARRAY_H