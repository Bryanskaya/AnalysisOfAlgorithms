#include "tests.h"


bool test(matrix_t& c)
{
    vector<int> res1, res2;
    int len1, len2;

    len1 = full_search(c, c.size(), res1);
    len2 = ant_search(0.5, 0.5, c, 100, res2);

    if (len1 == len2 || res1.size() == 0 && res2.size() == 0)
        return true;
    else
        return false;
}
void test_standart(matrix_t& c)
{
    cout << endl << __FUNCTION__;
    if (test(c))
        cout << ":\tPASSED\n";
    else
        cout << ":\tFAILED\n";
}

void test_size_2(matrix_t& c)
{
    cout << endl << __FUNCTION__;
    if (test(c))
        cout << ":\tPASSED\n";
    else
        cout << ":\tFAILED\n";
}

void test_no_solution(matrix_t& c)
{
    cout << endl << __FUNCTION__;
    if (test(c))
        cout << ":\tPASSED\n";
    else
        cout << ":\tFAILED\n";
}

void test_equal(matrix_t& c)
{
    cout << endl << __FUNCTION__;
    if (test(c))
        cout << ":\tPASSED\n";
    else
        cout << ":\tFAILED\n";
}

void run_tests()
{
    matrix_t c1 = { {0, 1, 2}, {1, 0, 3}, {2, 3, 0} };
    matrix_t c2 = { {0, 10}, {10, 0} };
    matrix_t c3 = { {0, 0, 17}, {0, 0, 0}, {17, 0, 0} };
    matrix_t c4 = { {0, 4, 4}, {4, 0, 4}, {4, 4, 0} };

    test_standart(c1);
    test_size_2(c2);
    test_no_solution(c3);
    test_equal(c4);
}