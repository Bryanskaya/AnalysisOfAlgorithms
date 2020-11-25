#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "search.h"
#include "measure_time.h"
#include "tests.h"


using namespace std;

sp_arr read_file(string filename)
{
	string line, delimiter = " : ";
	sp_arr  arr;
	s_p elem;

	ifstream in(filename);
	if (in.is_open())
	{
		while (getline(in, line))
		{
			elem.key = line.substr(0, line.find(delimiter));
			elem.value = line.substr(line.find(delimiter) + delimiter.length());

			arr.push_back(elem);
		}
	}
	in.close();

	return arr;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	string key, filename = "../generator/sites.txt";
	int choice;
	s_p result;

	cout << "Введите ключ: ";
	cin >> key;

	sp_arr data = read_file(filename), data_sorted = read_file(filename), data_sgm = read_file(filename);
	sgm_arr sgm_data;

	vector<double> time_full, time_ordered, time_sgm;

	
	while (true)
	{
		cout << "\nВыберете алгоритм: \n";
		cout << "1 - Поиск полным перебором\n";
		cout << "2 - Поиск в упорядоченном массиве\n";
		cout << "3 - Поиск по сегментам\n";
		cout << "4 - Замеры времени\n";
		cout << "5 - Тесты\n";
		cout << "\nДругое - выход\n";

		cout << "\n\nВаш выбор: ";
		cin >> choice;

		if (choice == 1)
		{
			result = full_search(key, data);
		}
		else if (choice == 2)
		{
			sort_arr(data);
			result = ordered_search(key, data);
		}
		else if (choice == 3)
		{
			sgm_data = split_segments(data);
			result = segment_search(key, sgm_data);
		}
		else if (choice == 4)
		{
			cout << "\n-----Поиск полным перебором-----\n" << endl;
			measure_time(full_search, data);

			cout << "\n-----Поиск в упорядоченном массиве-----\n" << endl;
			sort_arr(data_sorted);
			measure_time(ordered_search, data_sorted);

			cout << "\n-----Поиск по сегментам-----\n" << endl;
			sgm_data = split_segments(data);
			measure_time_sgm(segment_search, sgm_data);
		}
		else if (choice == 5)
			run_tests(data);
		else
			break;

		if (result.key != "")
			cout << endl << result.key << " " << result.value << endl;
		else if (choice != 4 && choice != 5)
			cout << "\nНе найдено!\n";
   }
}
