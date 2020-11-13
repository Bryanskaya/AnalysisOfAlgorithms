#include "test_time.h"


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