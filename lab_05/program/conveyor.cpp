#include "conveyor.h"

mutex set_mutex;

void process_thread_1(queue<shared_ptr<task>>& q_in, queue<shared_ptr<task>>& q_out)
{
    while (!q_in.empty()) {
        shared_ptr<task> ptr(q_in.front());
        q_in.pop();

        double t = get_measured();
        ptr->time_in_1 = t;
        
        xor_simple(ptr->str, ptr->key);

        t = get_measured();
        ptr->time_out_1 = t;

        set_mutex.lock();
        q_out.push(ptr);
        set_mutex.unlock();
    }
}

void process_thread_2(queue<shared_ptr<task>>& q_in, queue<shared_ptr<task>>& q_out, int count)
{
    for (int i = 0; i < count; i++)
    {
        while (q_in.empty()) {}

        shared_ptr<task> ptr(q_in.front());
        set_mutex.lock();
        q_in.pop();
        set_mutex.unlock();

        double t = get_measured();
        ptr->time_in_2 = t;

        vigenere_code(ptr->str, ptr->key);

        t = get_measured();
        ptr->time_out_2 = t;

        set_mutex.lock();
        q_out.push(ptr);
        set_mutex.unlock();
    }
}

void process_thread_3(queue<shared_ptr<task>>& q_in, queue<shared_ptr<task>>& q_out, int count)
{
    for (int i = 0; i < count; i++)
    {
        while (q_in.empty()) {}

        shared_ptr<task> ptr(q_in.front());
        set_mutex.lock();
        q_in.pop();
        set_mutex.unlock();

        double t = get_measured();
        ptr->time_in_3 = t;

        transposition(ptr->str);

        t = get_measured();
        ptr->time_out_3 = t;

        q_out.push(ptr);
    }
}