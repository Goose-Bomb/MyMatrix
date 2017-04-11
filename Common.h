#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<memory.h>
#include<stdint.h>
#include<float.h>

#define EPS 5e-6
#define POW2(X) (X)*(X)

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