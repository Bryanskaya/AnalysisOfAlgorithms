#include <iostream>

#include "bubble_sort.h"
#include "insert_sort.h"
#include "lsd_sort.h"
#include "tests.h"


using namespace std;

void sort(void(*f)(array_t&, int))
{
    cout << endl << "---Сортируется массив А[N]---" << endl;
    cout << "Введите значение N: ";
    int n;
    cin >> n;

    array_t arr = create_array(n);
    cout << endl;

    cout << "Введите массив А: " << endl;
    fill_array(arr, n);
    cout << endl;

    f(arr, n);

    cout << "Результат: " << endl;
    print_array(arr, n);

    free_array(&arr);
}

int main()
{
    setlocale(LC_ALL, "Russian");
  
    cout << "1 - Сортировка массива" << endl;
    cout << "2 - Тестирование алгоритмов" << endl;
    cout << "Ваш выбор: ";

    int cmd;
    cin >> cmd;

    switch (cmd)
    {
    case 1:
        cout << endl << "1 - Сортировка пузырьком" << endl;
        cout << "2 - Сортировка вставками" << endl;
        cout << "3 - Поразрядная сортировка" << endl;
        cout << "Ваш выбор: ";
        cin >> cmd;
        switch (cmd)
        {
        case 1:
            sort(bubble_sort);
            break;
        case 2:
            sort(insert_sort);
            break;
        case 3:
            sort(lsd_sort);
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

    return 0;
}
