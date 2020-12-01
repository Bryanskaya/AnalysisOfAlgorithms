#ifndef FULL_SEARCH_H
#define FULL_SEARCH_H

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


typedef vector<vector<int>> matrix_t;

int full_search(matrix_t& c, int n, vector<int>& result);

#endif // FULL_SEARCH_H