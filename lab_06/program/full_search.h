#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


typedef vector<vector<int>> matrix_t;

void full_search(matrix_t& c, int n);

#endif // MATRIX_H