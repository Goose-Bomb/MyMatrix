#include "Matrix.h"
#include "Vector.h"

int main(void)
{
	uint8_t i, j;
	matrix A, B;

	A = mat_input();
	vector b;
	b.len = 3;
	b = vec_input();
	
	puts("The result of Jacobi method is");
	vec_show(jacobi(A, b));

	system("pause");
	return 0;
}