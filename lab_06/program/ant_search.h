#ifndef ANT_SEARCH_H
#define ANT_SEARCH_H

#include <iostream>
#include <vector>

#define INIT_PHR	0.1
#define MIN_K_PHR	0.1

using namespace std;

typedef vector<vector<double>> matrix_double_t;
typedef vector<vector<int>> matrix_t;

typedef struct
{
	vector<int> done_path;
	int cur_pos;
	int len_path;
}ant_t;

double find_avg_path(matrix_t& c);
int ant_search(double a, double b, matrix_t& c, double k_vpr, double q, int t_max, vector<int>& result);

#endif // ANT_SEARCH_H