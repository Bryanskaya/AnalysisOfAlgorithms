#ifndef CONVEYOR_H
#define CONVEYOR_H

#include <iostream>
#include <queue>
#include <string>

#include "queue.h"
#include "codings.h"
#include "test_time.h"

using namespace std;


void process_thread_1(queue<shared_ptr<task>> &q_in, queue<shared_ptr<task>>& q_out);
void process_thread_2(queue<shared_ptr<task>>& q_in, queue<shared_ptr<task>>& q_out, int count);
void process_thread_3(queue<shared_ptr<task>>& q_in, queue<shared_ptr<task>>& q_out, int count);


#endif // CONVEYOR_H