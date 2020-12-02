#include "measure_time.h"

double PCFreq = 0.0;
__int64 CounterStart = 0;

void start_measuring()
{
    LARGE_INTEGER li;
    QueryPerformanceFrequency(&li);

    PCFreq = double(li.QuadPart) / 1000;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double get_measured()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);

    return double(li.QuadPart - CounterStart) / PCFreq;
}

void run_measuring_time(int size)
{
    matrix_t c = random_matrix(0, 100, size);
    vector<int> res;
    double q = find_avg_path(c);
    int count = 0;

    cout << "-> Количество городов: " << size << "\t";

    start_measuring();
    while (get_measured() < 3 * 1000)
    {
        ant_search(0.5, 0.5, c, 0.8, q, 30, res);
        count++;
    }

    double t = get_measured() / 1000 / count;
    cout << t << endl;
}