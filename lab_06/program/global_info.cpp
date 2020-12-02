#include "global_info.h"

using namespace std;

matrix_t input_matrix(int n)
{
    matrix_t c;
    int temp;

    cout << "\nВведите верхний треугольник матрицы:\n";
    cout << "- ";

    for (int i = 0; i < n - 1; i++)
    {
        vector<int> str;

        for (int k = 0; k < i; k++)
            str.push_back(c[k][i]);
        str.push_back(0);

        for (int j = 0; j < n - 1 - i; j++)
        {
            cin >> temp;
            str.push_back(temp);
        }

        c.push_back(str);

        for (int j = 0; j <= i; j++)
            cout << c[j][i + 1] << " ";
        cout << "- ";
    }

    vector<int> str;
    for (int i = 0; i < n - 1; i++)
        str.push_back(c[i][n - 1]);
    str.push_back(0);

    c.push_back(str);

    return c;
}

matrix_t random_matrix(int start, int end, int n)
{
    matrix_t c;
    int temp;

    for (int i = 0; i < n; i++)
    {
        vector<int> str;

        for (int j = 0; j < n; j++)
            str.push_back(0);

        c.push_back(str);
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            c[i][j] = rand() % (int)(end - start) + start;
            c[j][i] = c[i][j];
        }

    return c;
}

void print_matrix(matrix_t& c)
{
    for (int i = 0; i < c.size(); i++)
    {
        for (int j = 0; j < c[i].size(); j++)
        {
            if (i != j)
                cout << c[i][j] << " ";
            else
                cout << " - ";
        }
        cout << endl;
    }
}

params_t create_params(double a, double q, double ro, int t_max)
{
    params_t prm;

    prm.a = a;
    prm.b = 1 - a;
    prm.q = q;
    prm.ro = ro;
    prm.t_max = t_max;

    return prm;
}

void find_params(matrix_t& c, int goal_len)
{
    int cur_len, min_len = 1e5;
    vector<int> temp_res, result;
    params_t prm, prm_res;
    double q = find_avg_path(c);

    for (double a = 0; a <= 1; a += 0.1)
    {
        double b = 1 - a;

        for (double ro = 0; ro <= 1; ro += 0.1)
        {
            int temp_min = 1e5;
            prm = create_params(a, q, ro, 30);

            for (int k = 0; k < 3; k++)
            {
                cur_len = ant_search(prm.a, prm.b, c, prm.ro, prm.q, prm.t_max, temp_res);
                if (cur_len < temp_min)
                {
                    temp_min = cur_len;
                    result = temp_res;
                }
            }

            cout << prm.a << " " << prm.ro << " " << prm.t_max << " " << temp_min << " " << temp_min - goal_len << endl;

            if (temp_min < min_len)
            {
                min_len = temp_min;
                prm_res = prm;
            }

        }
        cout << endl;
    }

    cout << "Наилучший набор параметров для данной задачи: " << prm_res.a << " " << prm_res.b << " " << prm_res.ro << " " << prm_res.t_max << endl;

    cout << "Найденный путь: ";
    for (int i = 0; i < result.size(); i++)
        cout << result[i] << " ";
    cout << "\nЕго длина: " << min_len << endl;
}