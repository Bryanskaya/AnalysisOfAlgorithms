#ifndef SEARCH_H
#define SEARCH_H


#include <iostream>
#include <vector>
#include <string>

using namespace std;

using s_p = struct
{
	string key;
	string value;
};

using sp_arr = vector<s_p>;

using sgm = struct
{
	vector<string> key;
	sp_arr value;
};

using sgm_arr = vector<sgm>;

s_p not_found();

void sort_arr(sp_arr& data);
sgm_arr split_segments(sp_arr& data);

s_p full_search(string key, sp_arr& data);
s_p ordered_search(string key, sp_arr& data);
s_p segment_search(string key, sgm_arr& data);


#endif // SEARCH_H
