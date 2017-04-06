#pragma once
#include "Common.h"

typedef struct {
	uint32_t len;
	double* vec;
}vector;

vector vec_input(void);
void vec_show(vector);
double dot(vector, vector);
vector cross(vector, vector);
vector vec_calc(vector, vector, CALC_OPERATOR);
vector vec_abs(vector);
double vec_max(vector);
double vec_min(vector);


