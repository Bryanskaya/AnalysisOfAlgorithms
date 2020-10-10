#include <iostream>
#include <vector>

#include "standart_mult.h"
#include "winograd_mult.h"
#include "tests.h"


using namespace std;


void matrix_mult(matrix_t(*f)(matrix_t, matrix_t, int, int, int))
{
    cout << endl << "---Умножаются матрицы А[MxN] и B[NxQ]---" << endl;
    cout << "Введите значения M, N, Q: ";
    int m, n, q;
    cin >> m >> n >> q;

    matrix_t a = create_matrix(m, n);
    matrix_t b = create_matrix(n, q);
    cout << endl;

    cout << "Введите матрицу А: " << endl;
    fill_matrix(a, m, n);
    cout << endl;

    cout << "Введите матрицу В: " << endl;
    fill_matrix(b, n, q);
    cout << endl;

    matrix_t c = f(a, b, m, n, q);

    cout << "Результат: " << endl;
    print_matrix(c, m, q);

    free_matrix(&a, m, n);
    free_matrix(&b, n, q);
    free_matrix(&c, m, q);
}

void test_range(vector<int> &n)
{
    for (int key : n)
    {
        cout << endl << endl << "Размер тестируемых матриц: " << key << "x" << key << endl;

        cout << endl << "-----Standart-----" << endl;
        test_time(standart_mult, key);
        cout << endl << "-----Winograd-----" << endl;
        test_time(winograd_mult, key);
        cout << endl << "-----Winograd(improved)-----" << endl;
        test_time(winograd_opt_mult, key);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "1 - Умножение матриц" << endl;
    cout << "2 - Тестирование алгоритмов" << endl;
    cout << "Ваш выбор: ";

    int cmd;
    cin >> cmd;

    switch (cmd)
    {
    case 1:
        cout << endl << "1 - Классический алгоритм умножения матриц" << endl;
        cout << "2 - Алгоритм Винограда" << endl;
        cout << "Ваш выбор: ";
        cin >> cmd;
        switch (cmd)
        {
        case 1:
            matrix_mult(standart_mult);
            break;
        case 2:
            matrix_mult(winograd_mult);
            break;
        default:
            cout << "Некорректный ввод" << endl;
            return -1;
        }
        break;
    case 2:
        run_tests();
        break;
    default:
        cout << "Некорректный ввод" << endl;
        return -1;
    }

    /*vector<int> n1{ 50, 100, 200, 300, 400, 500, 600, 700 };
    vector<int> n2{ 51, 101, 201, 301, 401, 501, 601, 701 };
    test_range(n1);
    test_range(n2);*/

    return 0;
}

