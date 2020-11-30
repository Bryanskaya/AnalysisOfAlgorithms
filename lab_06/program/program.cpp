#include <iostream>
#include <time.h>

#include "full_search.h"
#include "ant_search.h"


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

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
                cout << c[i][j] << " ";
            else
                cout << " - ";
        }
        cout << endl;
    }

    return c;
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");

    int n, choice, cur_len, min_len = 1e7;
    matrix_t c;
    vector<int> temp_res, result;
    double j;

    cout << "Введите количество городов: ";
    cin >> n;

    if (n <= 1)
    {
        cout << "ERROR: incorrect input\n";
        return -1;
    }

    //c = input_matrix(n);
    c = random_matrix(0, 100, n);

    while (true)
    {
        cout << "\n\n1 - Полный перебор\n";
        cout << "2 - Муравьиный алгоритм\n";
        cout << "Другое - выход\n";

        cout << "\nВаш выбор: ";
        cin >> choice;

        cout << endl;

        if (choice == 1)
        {
            full_search(c, n);
        }
        else if (choice == 2)
        {
            for (double i = 0.0; i <= 1.0; i += 0.1)
            {
                for (double q = 0.0; q <= 1.0; q += 0.1)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        cur_len = ant_search(i, 1 - i, c, q, temp_res);
                        if (cur_len < min_len)
                        {
                            min_len = cur_len;
                            result = temp_res;
                        }
                    }

                    if (abs(i - 1) < 1e-3)
                        j = 0;
                    else
                        j = 1 - i;

                    cout << i << " " << j << " " << q << " " << cur_len << endl;
                }
                cout << endl;
            }

            cout << "Found tour: ";
            for (int i = 0; i < result.size(); i++)
                cout << result[i] << " ";
            cout << "\nIts length: " << min_len << endl;
        }
        else
            break;
    }

    return 0;
}

