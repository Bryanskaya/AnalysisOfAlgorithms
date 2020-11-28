#include "full_search.h"


matrix_t create_permutations(int n)
{
	vector<int> vct;
	matrix_t res;

	for (int i = 0; i < n; i++)
		vct.push_back(i);

	res.push_back(vct);
	while (next_permutation(vct.begin(), vct.end()))
		res.push_back(vct);

	return res;
}

bool way_is_exist(vector<int> vect, matrix_t& c)
{
	for (int i = 0; i < vect.size(); i++)
		if (c[vect[i]][vect[(i + 1) % vect.size()]] == 0)
			return false;

	return true;
}

int find_cost(vector<int> vect, matrix_t& c)
{
	int res = 0;

	for (int i = 0; i < vect.size(); i++)
		res += c[vect[i]][vect[(i + 1) % vect.size()]];

	return res;
}

void full_search(matrix_t& c, int n)
{
	vector<int> temp, tour;
	matrix_t prm = create_permutations(n);
	int num = prm.size(), min = 1e5, cost;

	for (int i = 0; i < num; i++)
	{
		temp = prm[i];
		if (way_is_exist(temp, c))
		{
			cost = find_cost(temp, c);

			if (cost < min)
			{
				min = cost;
				tour = temp;
			}
		}
	}

	cout << "Found tour: ";
	for (int i = 0; i < tour.size(); i++)
		cout << tour[i] << " ";
	cout << endl;

	cout << "Its length: " << min << endl;
}