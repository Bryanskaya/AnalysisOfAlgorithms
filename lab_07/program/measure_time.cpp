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

void measure_time(func_t f, sp_arr& data)
{
	double min_t = 1e5, max_t = -1, avg_t = 0, t;
	string key, not_exist_key = "123456.com";
    int count;

	for (size_t i = 0; i < data.size(); i++)
	{
		key = data[i].key;

        count = 0;

        start_measuring();

        while (get_measured() < 0.07 * 1000)
        {
            f(key, data);
            count++;
        }

        t = get_measured() / 1000 / count;

        cout << i + 1;
        cout.width(10);
        cout << " ";
        cout.width(6);
        cout << t << endl;

        if (min_t > t)
            min_t = t;
        if (max_t < t)
            max_t = t;
        avg_t += t;
	}

    avg_t /= data.size();

    count = 0;
    start_measuring();
    while (get_measured() < 0.07 * 1000)
    {
        f(not_exist_key, data);
        count++;
    }

    t = get_measured() / 1000 / count;
    cout << "NOT EXISTS" ;
    cout.width(3);
    cout << " ";
    cout.width(6);
    cout << t << endl;

    cout << "\nМаксимальное время:\t" << max_t << endl;
    cout << "Минимальное время:\t" << min_t << endl;
    cout << "Среднее время:\t\t" << avg_t << endl;
}

void measure_time_sgm(func_sgm_t f, sgm_arr& data)
{
    double min_t = 1e5, max_t = -1, avg_t = 0, t;
    string key, not_exist_key = "123456.com";
    int count, ind = 0, num_elem = 0;

    for (size_t i = 0; i < data.size(); i++)
    {
        num_elem += data[i].value.size();
        for (size_t j = 0; j < data[i].value.size(); j++)
        {
            ind++;

            key = data[i].value[j].key;

            count = 0;

            start_measuring();

            while (get_measured() < 0.03 * 1000)
            {
                f(key, data);
                count++;
            }

            t = get_measured() / 1000 / count;

            cout << ind;
            cout.width(10);
            cout << " ";
            cout.width(6);
            cout << t << endl;

            if (min_t > t)
                min_t = t;
            if (max_t < t)
                max_t = t;
            avg_t += t;
        }
    }

    avg_t /= num_elem;

    count = 0;
    start_measuring();
    while (get_measured() < 0.07 * 1000)
    {
        f(not_exist_key, data);
        count++;
    }

    t = get_measured() / 1000 / count;
    cout << "NOT EXISTS";
    cout.width(3);
    cout << " ";
    cout.width(6);
    cout << t << endl;

    cout << "\nМаксимальное время:\t" << max_t << endl;
    cout << "Минимальное время:\t" << min_t << endl;
    cout << "Среднее время:\t\t" << avg_t << endl;
}