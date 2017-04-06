#include "Matrix.h"
#include "Vector.h"

int main(void)
{
	/*
	matrix A,B;
	A = mat_input();
	vector b;
	b.len = 3;
	b = vec_input();
	
	puts("The result of Jacobi method is");
	vec_show(jacobi(A, b));
	*/

	vector a, b;
	a = vec_input(), b = vec_input();;

	printf("%f\n", angle(a, b));
	system("pause");
	return 0;
}