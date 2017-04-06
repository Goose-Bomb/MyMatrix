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

void ERROR_Handler(char*);
double pow2(double);