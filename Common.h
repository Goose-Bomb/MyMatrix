#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<memory.h>
#include<stdint.h>
#include<float.h>

#define EPS 1e-6

typedef enum{
    ADD, SUB, MUL, DIV
}CALC_OPERATOR;

typedef enum {
	NORM_TYPE_1 = 1,
	NORM_TYPE_2 = 2,
	NORM_TYPE_INF = 3,
	NORM_TYPE_FRO = 4,
}NORM_TYPE;

void ERROR_Handler(char*);
double pow2(double);