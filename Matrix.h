#pragma once
#include "Common.h"
#include "Vector.h"

typedef struct {
	double** mat;
	uint8_t row, col;
}matrix;

typedef enum {
	NORM_TYPE_1 = 1,
	NORM_TYPE_2 = 2,
	NORM_TYPE_INF = 3,
	NORM_TYPE_FRO = 4,
}NORM_TYPE;


void swap_row(double**, uint8_t, uint8_t);
double trace(matrix);
double det(matrix);
double norm(matrix, NORM_TYPE);
double cond(matrix, NORM_TYPE);
matrix eye(uint8_t);
matrix trans(matrix);
matrix inv(matrix);
matrix mat_calc(matrix, matrix, CALC_OPERATOR);
matrix mat_mul(matrix, matrix);
matrix mat_input(void);
matrix mat_copy(matrix);
void mat_show(matrix);
void mat_delete(matrix);
vector jacobi(matrix, vector);
vector gauss_seidel(matrix, vector);
extern void ERROR_Handler(char*);
extern vector vec_input(void);