#include "Vector.h"

vector vec_input(void)
{
	puts("Please input the length of the vector");

	vector x;
	scanf("%u", &x.len);

	x.vec = (double*)malloc(x.len * sizeof(double));

	puts("Please input the elements of the vector");

	for (size_t i = 0; i < x.len; i++)
	{
		scanf("%lf", &x.vec[i]);
	}

	return x;
}

void vec_show(vector x)
{
	uint32_t i;
	for (i = 0; i < x.len; i++) printf("%g ", x.vec[i]);
	putchar('\n');
}


double dot(vector A, vector B)
{
	if (A.len != B.len)
	{
		ERROR_Handler("Error : Tow vectors must have the same len!");
	}

	double result = 0.0;

	for (uint32_t i = 0; i < A.len; i++, result += A.vec[i] * B.vec[i]);
	return result;
}

double angle(vector x, vector y)
{
	return acos(dot(x, y) / vec_norm(x, NORM_TYPE_2) / vec_norm(y, NORM_TYPE_2));
}

vector cross(vector A, vector B)
{
	if (A.len != 3 || B.len != 3)
	{
		ERROR_Handler("Error : Length of the vectors must be 3!");
	}

	vector C;
	C.len = 3;
	C.vec = (double*)malloc(3 * sizeof(double));

	C.vec[0] = A.vec[1] * B.vec[2] - A.vec[2] * B.vec[1];
	C.vec[1] = A.vec[2] * B.vec[0] - A.vec[0] * B.vec[2];
	C.vec[2] = A.vec[0] * B.vec[1] - A.vec[1] * B.vec[0];

	return C;
}

vector vec_calc(vector A, vector B, CALC_OPERATOR operator)
{
	if (A.len != B.len)
	{
		ERROR_Handler("Error : Tow vectors must have the same len!");
	}

	vector C;
	C.len = A.len;
	C.vec = (double*)malloc(C.len * sizeof(double));

	for (uint32_t i = 0; i < A.len; i++)
	{
		switch (operator)
		{
		case ADD: C.vec[i] = A.vec[i] + B.vec[i]; break;
		case SUB: C.vec[i] = A.vec[i] - B.vec[i]; break;
		case MUL: C.vec[i] = A.vec[i] * B.vec[i]; break;
		case DIV: C.vec[i] = A.vec[i] / B.vec[i]; break;
		}
	}

	return C;
}

double vec_max(vector x)
{
	double result = -DBL_MAX;

	for (uint32_t i = 0; i < x.len; i++) result = __max(result, x.vec[i]);
	return result;
}

double vec_min(vector x)
{
	double result = DBL_MAX;

	for (uint32_t i = 0; i < x.len; i++) result = __min(result, x.vec[i]);
	return result;
}

vector vec_abs(vector x)
{
	vector abs_x;
	abs_x.len = x.len;
	abs_x.vec = (double*)malloc(abs_x.len * sizeof(double));

	for (uint32_t i = 0; i < abs_x.len; i++) abs_x.vec[i] = fabs(x.vec[i]);
	return abs_x;
}

double vec_norm(vector x, NORM_TYPE type)
{
	double norm = 0.0;

	switch (type)
	{
	case NORM_TYPE_1:
		for (uint32_t i = 0; i < x.len; norm += fabs(x.vec[i++]));
		return norm;

	case NORM_TYPE_2:
		for (uint32_t i = 0; i < x.len; norm += POW2(x.vec[i++]));
		return sqrt(norm);

	case NORM_TYPE_INF:
		for (uint32_t i = 0; i < x.len; norm = __max(norm, fabs(x.vec[i++])));
		return norm;
	}
}