#ifndef MEASURE_TIME_H
#define MEASURE_TIME_H


#include <windows.h>

#include "search.h"

typedef s_p(*func_t)(string, sp_arr&);
typedef s_p(*func_sgm_t)(string, sgm_arr&);

void measure_time(func_t f, sp_arr&);
void measure_time_sgm(func_sgm_t f, sgm_arr&);


#endif // MEASURE_TIME_H