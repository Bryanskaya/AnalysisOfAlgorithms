#include "ant_search.h"

matrix_double_t create_pheromone(int n)
{
	matrix_double_t res;
	vector<double> temp;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			temp.push_back(INIT_PHR);
		res.push_back(temp);
	}

	return res;
}

double find_avg_path(matrix_t& c)
{
	int n = c.size();
	double res = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			res += c[i][j];

	return res / n;
}

vector<ant_t> create_colony(int n)
{
	vector<ant_t> res;

	for (int i = 0; i < n; i++)
	{
		ant_t ant;
		ant.done_path.push_back(i);
		ant.cur_pos = i;
		ant.len_path = 0;

		res.push_back(ant);
	}

	return res;
}

bool is_exist(int index, vector<int> path)
{
	for (int i = 0; i < path.size(); i++)
		if (path[i] == index)
			return true;
	return false;
}

void update_ant(int new_pos, int len, ant_t& ant)
{
	ant.done_path.push_back(new_pos);
	ant.len_path += len;
	ant.cur_pos = new_pos;
}

int find_next_top(matrix_t& c, vector<int>& pos_path, ant_t& ant, matrix_double_t& phr, double a, double b)
{
	int k = 0;
	vector<double> p;
	double p_temp, sum = 0, cur_sum = 0, comp_p;

	for (int i = 0; i < pos_path.size(); i++)
	{
		int node = pos_path[i];
		if (c[ant.cur_pos][node])
			p_temp = pow(phr[ant.cur_pos][node], a) / pow(c[ant.cur_pos][node], b);
		else
			p_temp = 0;

		p.push_back(p_temp);
		sum += p_temp;
	}

	if (sum == 0)
		return -1;

	comp_p = (double)rand() / RAND_MAX * sum;

	while (cur_sum < comp_p)
	{
		cur_sum += p[k];
		k++;
	}

	return k-1;
}

void find_path(matrix_t& c, matrix_double_t& phr, ant_t& ant, double a, double b)
{
	vector<int> pos_path;
	int ind, flag = 1;

	for (int i = 0; i < c.size(); i++)
		if (i != ant.cur_pos)
			pos_path.push_back(i);

	while (pos_path.size() != 0)
	{
		ind = find_next_top(c, pos_path, ant, phr, a, b);
		if (ind == -1)
			break;

		update_ant(pos_path[ind], c[ant.cur_pos][pos_path[ind]], ant);

		pos_path.erase(pos_path.begin() + ind);
		if (pos_path.size() == 0 && flag)
		{
			pos_path.push_back(ant.done_path[0]);
			flag = 0;
		}
	}
}

void find_vaporization(matrix_double_t& phr, double k)
{
	for (int i = 0; i < phr.size(); i++)
		for (int j = 0; j < phr[i].size(); j++)
			phr[i][j] = (1 - k) * phr[i][j];
}

void increase_phr(matrix_double_t& pheromone, vector<ant_t> colony, double q)
{
	for (int i = 0; i < colony.size(); i++)
		for (int j = 0; j < colony[i].done_path.size() - 1; j++)
		{
			int node1 = colony[i].done_path[j];
			int node2 = colony[i].done_path[j+1];
			pheromone[node1][node2] += q / colony[i].len_path;
			if (pheromone[node1][node2] < MIN_K_PHR * INIT_PHR)
				pheromone[node1][node2] = MIN_K_PHR * INIT_PHR;
			pheromone[node2][node1] = pheromone[node1][node2];
		}
}

void elite_increase(double q, vector<int>& tour, int len, matrix_double_t& phr)
{
	int num_el_ant = 2;

	if (!tour.size())
		return;

	for (int i = 0; i < tour.size() - 1; i++)
	{
		int node1 = tour[i];
		int node2 = tour[i + 1];

		phr[node1][node2] += num_el_ant * q / len;
		phr[node2][node1] += num_el_ant * q / len;
	}
}

int ant_search(double a, double b, matrix_t& c, double k_vpr, vector<int>& result)
{
	double q = find_avg_path(c);
	matrix_double_t pheromone = create_pheromone(c.size());
	int t_max = 100, len = 1e7;
	vector<int> tour;

	for (int t = 0; t < t_max; t++)
	{
		vector<ant_t> colony = create_colony(c.size());

		for (int i = 0; i < colony.size(); i++)
		{
			find_path(c, pheromone, colony[i], a, b);
			if (colony[i].len_path < len && colony[i].done_path.size() == c.size() + 1)
			{
				len = colony[i].len_path;
				tour = colony[i].done_path;
			}
		}

		find_vaporization(pheromone, k_vpr);

		elite_increase(q, tour, len, pheromone);

		increase_phr(pheromone, colony, q);
	}

	/*cout << "Found tour: ";
	for (int i = 0; i < tour.size(); i++)
		cout << tour[i] << " ";
	cout << "\nIts length: " << len << endl;*/

	result = tour;

	return len;
}