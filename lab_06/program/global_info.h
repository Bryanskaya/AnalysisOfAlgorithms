#ifndef GLOBAL_INFO_H
#define GLOBAL_INFO_H

#include <vector>
#include <iostream>

#include "ant_search.h"

using namespace std;

typedef vector<vector<int>> matrix_t;

typedef struct
{
	double a;
	double b;
	double ro;
	double q;
	int t_max;
}params_t;




matrix_t input_matrix(int n);
matrix_t random_matrix(int start, int end, int n);
void print_matrix(matrix_t& c);
void find_params(matrix_t& c, int goal_len);

#endif // GLOBAL_INFO_H
