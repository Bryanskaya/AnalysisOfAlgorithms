#include "queue.h"

using namespace std;


string generate_string(int length)
{
	string str;

	for (int i = 0; i < length; i++)
		str += char(rand() % 256);

	return str;
}

queue<shared_ptr<task>> organize_queue(int count, int len_str, int len_key)
{
	queue<shared_ptr<task>> q_tasks;

	for (int i = 0; i < count; i++)
	{
		string str = generate_string(len_str);
		string key_letter = generate_string(len_key);

		shared_ptr<task> ptr(new task);
		ptr->str = str;
		ptr->key = key_letter;

		q_tasks.push(ptr);
	}

	return q_tasks;
}