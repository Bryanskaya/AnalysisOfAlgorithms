#include "tests.h"


bool is_equal(s_p res, s_p ans)
{
	if (res.key == ans.key && res.value == ans.value)
		return true;
	return false;
}

void test_first_key(sp_arr& data)
{
	sgm_arr sgm_data;

	if (!is_equal(full_search(data[0].key, data), data[0]))
		cout << endl << __FUNCTION__ << " full_search " << ":\tFAILED\n";
	else
		cout << endl << __FUNCTION__ << "\tfull_search " << ":\tSUCCESS\n";

	sort_arr(data);
	if (!is_equal(ordered_search(data[0].key, data), data[0]))
		cout << __FUNCTION__ << " ordered_search " << ":\tFAILED\n";
	else
		cout << __FUNCTION__ << "\tordered_search " << ":\tSUCCESS\n";

	sgm_data = split_segments(data);
	if (!is_equal(segment_search(data[0].key, sgm_data), data[0]))
		cout << __FUNCTION__ << " segment_search " << ":\tFAILED\n";
	else
		cout << __FUNCTION__ << "\tsegment_search " << ":\tSUCCESS\n";
}

void test_each_100_key(sp_arr& data)
{
	sgm_arr sgm_data;
	int flag = 1;

	for (size_t i = 0; i < data.size(); i += 100)
		if (!is_equal(full_search(data[i].key, data), data[i]))
		{
			cout << endl << __FUNCTION__ << " full_search " << ":\tFAILED\n";
			flag = 0;
			break;
		}
	if (flag)
		cout << endl << __FUNCTION__ << "\tfull_search " << ":\tSUCCESS\n";

	flag = 1;
	sort_arr(data);
	for (size_t i = 0; i < data.size(); i += 100)
		if (!is_equal(ordered_search(data[i].key, data), data[i]))
		{
			cout << __FUNCTION__ << " ordered_search " << ":\tFAILED\n";
			flag = 0;
			break;
		}
	if (flag)
		cout << __FUNCTION__ << "\tordered_search " << ":\tSUCCESS\n";

	flag = 1;
	sgm_data = split_segments(data);
	for (size_t i = 0; i < data.size(); i += 100)
		if (!is_equal(segment_search(data[i].key, sgm_data), data[i]))
		{
			cout << __FUNCTION__ << " segment_search " << ":\tFAILED\n";
			flag = 0;
			break;
		}
	if (flag)
		cout << __FUNCTION__ << "\tsegment_search " << ":\tSUCCESS\n";
}

void test_last_key(sp_arr& data)
{
	sgm_arr sgm_data;

	if (!is_equal(full_search(data[data.size() - 1].key, data), data[data.size() - 1]))
		cout << endl << __FUNCTION__ << " full_search " << ":\tFAILED\n";
	else
		cout << endl << __FUNCTION__ << "\tfull_search " << ":\tSUCCESS\n";

	sort_arr(data);
	if (!is_equal(ordered_search(data[data.size() - 1].key, data), data[data.size() - 1]))
		cout << __FUNCTION__ << " ordered_search " << ":\tFAILED\n";
	else
		cout << __FUNCTION__ << "\tordered_search " << ":\tSUCCESS\n";

	sgm_data = split_segments(data);
	if (!is_equal(segment_search(data[data.size() - 1].key, sgm_data), data[data.size() - 1]))
		cout << __FUNCTION__ << " segment_search " << ":\tFAILED\n";
	else
		cout << __FUNCTION__ << "\tsegment_search " << ":\tSUCCESS\n";
}

void test_not_exist_key(sp_arr& data)
{
	sgm_arr sgm_data;
	s_p key_not_exst;

	key_not_exst.key = "123345";
	key_not_exst.value = "000";

	if (!is_equal(full_search(key_not_exst.key, data), not_found()))
		cout << endl << __FUNCTION__ << " full_search " << ":\tFAILED\n";
	else
		cout << endl << __FUNCTION__ << "\tfull_search " << ":\tSUCCESS\n";

	sort_arr(data);
	if (!is_equal(ordered_search(key_not_exst.key, data), not_found()))
		cout << __FUNCTION__ << " ordered_search " << ":\tFAILED\n";
	else
		cout << __FUNCTION__ << "\tordered_search " << ":\tSUCCESS\n";

	sgm_data = split_segments(data);
	if (!is_equal(segment_search(key_not_exst.key, sgm_data), not_found()))
		cout << __FUNCTION__ << " segment_search " << ":\tFAILED\n";
	else
		cout << __FUNCTION__ << "\tsegment_search " << ":\tSUCCESS\n";
}

void run_tests(sp_arr& data)
{
	cout << "----- START TESTING -----" << endl;

	test_first_key(data);
	test_each_100_key(data);
	test_last_key(data);
	test_not_exist_key(data);


	cout << endl << "----- FINISHED -----" << endl;
}