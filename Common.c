#include "Common.h"

double pow2(double x)
{
	return x*x;
}

//�쳣����
void ERROR_Handler(char* msg)
{
	printf("Error: %s\n", msg);
	system("pause");
	exit(0);
}