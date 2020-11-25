#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include <string>
#include <iostream>
#include <random>
#include <time.h>


using namespace std;


struct task
{
	string str;
	string key;

	double time_in_1;
	double time_out_1;

	double time_in_2;
	double time_out_2;

	double time_in_3;
	double time_out_3;
};


string generate_string(int length);
queue<shared_ptr<task>> organize_queue(int count, int len_str, int len_key);

#endif // QUEUE_H