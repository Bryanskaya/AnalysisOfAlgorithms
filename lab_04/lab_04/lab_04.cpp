#include <iostream>
#include <vector>
#include <memory>

#include "winograd_mult.h"
#include "parall_winograd.h"
#include "tests.h"


using namespace std; 


void matrix_mult_winograd()
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

    matrix_t c = winograd_mult(a, b, m, n, q);

    cout << "Результат: " << endl;
    print_matrix(c, m, q);

    free_matrix(&a, m, n);
    free_matrix(&b, n, q);
    free_matrix(&c, m, q);
}

void matrix_mult_parall()
{
    cout << endl << "---Умножаются матрицы А[MxN] и B[NxQ]---" << endl;
    cout << "Введите значения M, N, Q: ";
    int m, n, q, num_thread;
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

    cout << "Введите количество потоков: ";
    cin >> num_thread;

    matrix_t c = parall_winograd_mult_1(a, b, m, n, q, num_thread);

    cout << "Результат: " << endl;
    print_matrix(c, m, q);

    free_matrix(&a, m, n);
    free_matrix(&b, n, q);
    free_matrix(&c, m, q);
}

void test_range(int n, vector<int>& num_threads)
{
    for (int key : num_threads)
    {
        cout << endl << endl << "Размер тестируемых матриц: " << n << "x" << n << endl;
        cout << "Количество потоков: " << key;

        cout << endl << "-----Winograd(improved)-----" << endl;
        test_time_cons(winograd_mult, n);
        cout << endl << "-----Parallel Winograd(1)-----" << endl;
        test_time_parall(parall_winograd_mult_1, n, key);
        cout << endl << "-----Parallel Winograd(2)-----" << endl;
        test_time_parall(parall_winograd_mult_2, n, key);
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
        cout << endl << "1 - Алгоритм Винограда" << endl;
        cout << "2 - Распараллеленный алгоритм Винограда" << endl;
        cout << "Ваш выбор: ";
        cin >> cmd;
        switch (cmd)
        {
        case 1:
            matrix_mult_winograd();
            break;
        case 2:
            matrix_mult_parall();
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

    vector<int> num_threads{ 1, 2, 4, 8, 16, 32 };
    int n[] = { 100, 200, 400, 600, 800, 1000 };
    for (int key : n)
        test_range(key, num_threads);

    for (int key : n)
        test_range(key, num_threads);

    return 0;
}