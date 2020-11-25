#include "search.h"

using namespace std;


s_p not_found()
{
	s_p data;

	data.key = "";
	data.value = "";

	return data;
}

s_p full_search(string key, sp_arr& data)
{
	int len = data.size();

	for (int i = 0; i < len; i++)
		if (data[i].key == key)
			return data[i];

	return not_found();
}

void sort_arr(sp_arr& data)
{
	s_p temp;

	for (size_t i = 0; i < data.size() - 1; i++)
		for (size_t j = 0; j < data.size() - i - 1; j++)
			if (data[j].key > data[j + 1].key) {
				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}
}


s_p ordered_search(string key, sp_arr& data)
{
	int left = 0, right = data.size() - 1;

	while (right >= left) {
		int middle = (left + right) / 2;   

		if (data[middle].key < key) {
			left = middle + 1;
		}
		else if (data[middle].key > key) {
			right = middle - 1;
		}
		else
			return data[middle];
	}

	return not_found();
}


sgm_arr split_segments(sp_arr& data)
{
	sgm_arr arr;
	vector<string> keys_1 = { "ru", "com", "io" }, keys_2 = { "net", "biz", "org", "info" };
	string part_key;
	int flag = 0;

	for (size_t i = 0; i < keys_1.size(); i++)
	{
		sgm temp_1;

		temp_1.key.push_back(keys_1[i]);
		arr.push_back(temp_1);
	}

	for (size_t i = 0; i < keys_2.size() - 1; i += 2)
	{
		sgm temp_2;

		temp_2.key.push_back(keys_2[i]);
		temp_2.key.push_back(keys_2[i + 1]);

		arr.push_back(temp_2);
	}

	for (size_t i = 0; i < data.size(); i++)
	{
		flag = 0;
		part_key = data[i].key.substr(data[i].key.rfind('.') + 1);
		
		for (size_t j = 0; j < arr.size(); j++)
		{
			for (size_t k = 0; k < arr[j].key.size(); k++)
			{
				if (part_key == arr[j].key[k])
				{
					arr[j].value.push_back(data[i]);
					flag = 1;
					break;
				}
			}

			if (flag)
				break;
		}
	}

	return arr;
}

s_p segment_search(string key, sgm_arr& data)
{
	string part_key = key.substr(key.rfind('.') + 1);;

	for (size_t i = 0; i < data.size(); i++)
	{
		for (size_t j = 0; j < data[i].key.size(); j++)
			if (data[i].key[j] == part_key)
			{
				sp_arr& arr = data[i].value;
				return full_search(key, arr);
			}
	}

	return not_found();
}

