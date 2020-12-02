#include <iostream>
#include <time.h>

#include "full_search.h"
#include "ant_search.h"
#include "tests.h"
#include "measure_time.h"
#include "global_info.h"


using namespace std;


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
        cout << "ОШИБКА: неверный ввод\n";
        return -1;
    }

    //c = input_matrix(n);
    c = random_matrix(1, 1000, n);
    print_matrix(c);

    while (true)
    {
        cout << "\n\n1 - Полный перебор\n";
        cout << "2 - Муравьиный алгоритм\n";
        cout << "3 - Запустить тесты\n";
        cout << "4 - Измерить время для муравьиного алгоритма\n";
        cout << "Другое - выход\n";

        cout << "\nВаш выбор: ";
        cin >> choice;

        cout << endl;

        if (choice == 1)
        {
            min_len = full_search(c, n, result);

            cout << "Найденный путь: ";
            for (int i = 0; i < result.size(); i++)
                cout << result[i] << " ";
            cout << "\nЕго длина: " << min_len << endl;
        }
        else if (choice == 2)
        {
            min_len = full_search(c, n, result);

            find_params(c, min_len);

            /*min_len = ant_search(0.5, 0.5, c, 0.5, 100, 100, result);

            cout << "Found tour: ";
            for (int i = 0; i < result.size(); i++)
                cout << result[i] << " ";
            cout << "\nIts length: " << min_len << endl;*/
        }
        else if (choice == 3)
        {
            run_tests();
        }
        else if (choice == 4)
        {
            vector<int> sizes = { 2, 4, 8, 16, 32, 64, 128, 256, 512 };

            cout << "--- Измерение времени для муравьиного алгоритма ---\n";

            for (int i = 0; i < sizes.size(); i++)
                run_measuring_time(sizes[i]);
        }
        else
            break;
    }

    return 0;
}

