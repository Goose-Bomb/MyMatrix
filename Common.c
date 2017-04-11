#include "Common.h"

//“Ï≥£¥¶¿Ì
void ERROR_Handler(char* msg)
{
	printf("Error: %s\n", msg);
	system("pause");
	exit(0);
}