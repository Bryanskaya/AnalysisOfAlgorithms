#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>
#include <thread>

#include "codings.h"
#include "queue.h"
#include "conveyor.h"
#include "test_time.h"


using namespace std;


void do_task(int count)
{
    int length_str = 1000000;
    int length_key = 20;
    double t, cur_process, cur_delay, time_start, time_end;
    double max_process = -1, min_process = 1000000, avg_process = 0,
           max_delay = -1, min_delay = 1000000, avg_delay = 0;

    queue<shared_ptr<task>> q_tasks = organize_queue(count, length_str, length_key);
    queue<shared_ptr<task>> q_done_1, q_done_2, q_result;

    shared_ptr<task> temp;

    vector<thread> thread_arr;

    start_measuring();

    thread_arr.push_back(thread(process_thread_1, ref(q_tasks), ref(q_done_1)));
    thread_arr.push_back(thread(process_thread_2, ref(q_done_1), ref(q_done_2), count));
    thread_arr.push_back(thread(process_thread_3, ref(q_done_2), ref(q_result), count));

    for (int i = 0; i < thread_arr.size(); i++)
        thread_arr[i].join();

    cout << endl << endl << " #";
    cout.width(8); 
    cout << " ";
    cout << "1st process (in/out) ";
    cout.width(12);
    cout << " ";
    cout << " 2nd process (in/out) ";
    cout.width(12);
    cout << " ";
    cout << " 3d process (in/out)" << endl;
    cout << "--------------------------------------------------------------------------------------------------";
    cout << endl;

    for (int i = 0; i < count; i++)
    {
        temp = q_result.front();
        if (i == 0)
            time_start = temp->time_in_1;
        else if (i == count - 1)
            time_end = temp->time_out_3;

        cout << " ";
        cout.width(2); 
        cout << i + 1;
        cout.width(6);
        cout << " ";
        cout.width(10);
        cout << temp->time_in_1 << " - " << temp->time_out_1;
        cout.width(6);
        cout << " ";
        cout.width(18);
        cout << temp->time_in_2 << " - " << temp->time_out_2;
        cout.width(6);
        cout << " ";
        cout.width(18); 
        cout << temp->time_in_3 << " - " << temp->time_out_3 << endl;
        q_result.pop();

        cur_process = temp->time_out_3 - temp->time_in_1;
        if (cur_process > max_process)
            max_process = cur_process;
        if (cur_process < min_process)
            min_process = cur_process;

        avg_process += cur_process;

        cur_delay = temp->time_in_2 - temp->time_out_1;
        if (cur_delay > max_delay)
            max_delay = cur_delay;
        if (cur_delay < min_delay)
            min_delay = cur_delay;

        avg_delay += cur_delay;

        cur_delay = temp->time_in_3 - temp->time_out_2;
        if (cur_delay > max_delay)
            max_delay = cur_delay;
        if (cur_delay < min_delay)
            min_delay = cur_delay;

        avg_delay += cur_delay;
    }   
    avg_process /= count;
    avg_delay /= (count * 2);

    cout << endl;
    cout.width(21);
    cout << " ";
    cout << "Min";
    cout.width(15);
    cout << " ";
    cout << "Max";
    cout.width(15);
    cout << " ";
    cout << "Avg" << endl;

    cout << "Whole task";
    cout.width(10);
    cout << " ";
    cout << min_process;
    cout.width(10);
    cout << " ";
    cout << max_process;
    cout.width(10);
    cout << " ";
    cout << avg_process << endl;

    cout << "Delay";
    cout.width(16);
    cout << " ";
    cout << min_delay;
    cout.width(10);
    cout << " ";
    cout << max_delay;
    cout.width(10);
    cout << " ";
    cout << avg_delay << endl << endl;

    cout << "General time: " << time_end - time_start << endl;
}

int main()
{
    srand(time(NULL));

    int count;

    cout << "Input number of tasks: ";
    cin >> count;

    if (count <= 0)
    {
        cout << "ERROR";
        return -1;
    }

    do_task(count);

    return 0;
}

