#include <iostream>

#include "full_search.h"


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

int main()
{
    setlocale(LC_ALL, "Russian");

    int n, choice;
    matrix_t c;

    cout << "Введите количество городов: ";
    cin >> n;

    if (n <= 1)
    {
        cout << "ERROR: incorrect input\n";
        return -1;
    }

    c = input_matrix(n);

    while (true)
    {
        cout << "\n\n1 - Полный перебор\n";
        cout << "2 - Муравьиный алгоритм\n";
        cout << "3 - Замеры времени\n";
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
            //
        }
        else if (choice == 3)
        {
            //
        }
        else
            break;
    }

    return 0;
}

