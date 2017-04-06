#include "Matrix.h"

matrix mat_input(void)
{
	uint8_t i, j;
	matrix m;

	puts("Please input the size of the Matrix : [rows, cols]");
	scanf("%d%d", &m.row, &m.col);

	printf("Please input the elements of the %d * %d Matrix\n", m.row, m.col);

	m.mat = (double **)malloc(m.row * sizeof(double *));
	for (i = 0; i < m.row; i++)
	{
		m.mat[i] = (double *)malloc(m.col * sizeof(double));
		for (j = 0; j < m.col; j++)
		{
			scanf("%lf", &m.mat[i][j]);
		}
	}

	return m;
}

void mat_show(matrix m)
{
	putchar('\n');
	uint8_t i, j;
	for (i = 0; i < m.row; i++)
	{
		for (j = 0; j < m.col; j++)
		{
			printf("%g ", m.mat[i][j]);
		}
		putchar('\n');
	}
}

matrix mat_copy(matrix M)
{
	uint8_t i, j;
	matrix COPY;
	COPY.row = M.row;
	COPY.col = M.col;

	COPY.mat = (double **)malloc(COPY.row * sizeof(double *));
	for (i = 0; i < COPY.row; i++)
	{
		COPY.mat[i] = (double *)malloc(COPY.col * sizeof(double));
		for (j = 0; j < COPY.col; j++) COPY.mat[i][j] = M.mat[i][j];
	}
	return COPY;
}

void mat_delete(matrix M)
{
	while (M.col--) free(M.mat[M.col]);
	free(M.mat);
}

//产生一个单位阵
matrix eye(uint8_t n)
{
	matrix I;
	I.row = n;
	I.col = n;

	I.mat = (double **)malloc(n * sizeof(double *));
	for (uint8_t i = 0; i < n; i++)
	{
		I.mat[i] = (double *)malloc(n * sizeof(double));
		I.mat[i][i] = 1.0;
	}

	return I;
}

//将矩阵某两行交换
void swap_row(double** mat, uint8_t r1, uint8_t r2)
{
	double* t = mat[r1];
	mat[r1] = mat[r2];
	mat[r2] = t;
}

//求逆矩阵
matrix inv(matrix M)
{
	if (M.row != M.col) //非方阵，退出
	{
		ERROR_Handler("Not square matrix!");
	}

	uint8_t i, j, k;
	matrix result = eye(M.row), temp = mat_copy(M);

	for (i = 0; i < temp.row - 1; i++)
	{
		double pivot_element = temp.mat[i][i];
		uint8_t pivot_row = i;

		for (j = i + 1; j < temp.row; j++)
		{
			if (temp.mat[j][i] > pivot_element) //找最大的列主元
			{
				pivot_element = temp.mat[j][i];
				pivot_row = j;
			}
		}

		if (fabs(pivot_element - 0.0) < 1e-14) //列主元为0 说明矩阵不可逆
		{
			mat_delete(temp);
			ERROR_Handler("This is a singular matrix!");
		}

		if (pivot_row != i) //列主元所在行与第一行互换
		{
			swap_row(temp.mat, pivot_row, i);
			swap_row(result.mat, pivot_row, i);
		}

		for (j = i + 1; j < temp.row; j++) //进行初等行变换 化为上三角矩阵
		{
			if (fabs(temp.mat[j][i] - 0.0) < 1e-14) continue;

			double t = temp.mat[j][i] / temp.mat[i][i];
			temp.mat[j][i] = 0.0;

			for (k = i + 1; k < temp.row; k++)
				temp.mat[j][k] -= temp.mat[i][k] * t;

			for (k = 0; k < temp.row; k++)
				result.mat[j][k] -= result.mat[i][k] * t;
		}
	}

	for (i = temp.row - 1; i > 0; i--) //化成对角阵
	{
		if (fabs(temp.mat[i][i] - 0.0) < 1e-14)
		{
			mat_delete(temp);
			ERROR_Handler("This is a singular matrix!");
		}

		for (j = 0; j < i; j++)
		{
			double t = temp.mat[j][i] / temp.mat[i][i];
			for (k = 0; k < temp.row; k++) result.mat[j][k] -= result.mat[i][k] * t;
		}
	}

	for (i = 0; i < temp.row; i++)
		for (j = 0; j < temp.row; j++) result.mat[i][j] /= temp.mat[i][i];

	mat_delete(temp);
	return result;
}

matrix mat_calc(matrix A, matrix B, CALC_OPERATOR operator) //矩阵对应元素运算
{
	if (A.row != B.row || A.col != B.col)
	{
		ERROR_Handler("Tow matrixs must have the same size!");
	}

	uint8_t i, j;
	matrix C;
	C.row = A.row;
	C.col = A.col;
	C.mat = (double **)malloc(C.row * sizeof(double *));

	for (i = 0; i < C.row; i++)
	{
		C.mat[i] = (double *)malloc(C.col * sizeof(double));
		for (j = 0; j < C.col; j++)
		{
			switch (operator)
			{
			case ADD: C.mat[i][j] = A.mat[i][j] + B.mat[i][j]; break;
			case SUB: C.mat[i][j] = A.mat[i][j] - B.mat[i][j]; break;
			case MUL: C.mat[i][j] = A.mat[i][j] * B.mat[i][j]; break;
			case DIV: C.mat[i][j] = A.mat[i][j] / B.mat[i][j]; break;
			}
		}
	}

	return C;
}

matrix mat_mul(matrix A, matrix B) //矩阵相乘
{
	if (A.col != B.row)
	{
		ERROR_Handler("Tow matrix's size not match!");
	}

	uint8_t i, j, k;
	matrix C;
	C.row = A.row;
	C.col = B.col;
	C.mat = (double **)malloc(C.row * sizeof(double *));

	for (i = 0; i < C.row; i++)
	{
		C.mat[i] = (double *)malloc(C.col * sizeof(double));
		for (j = 0; j < C.col; j++)
		{
			for (k = 0; k < A.col; k++) C.mat[i][j] += A.mat[i][k] * B.mat[k][j];
		}
	}

	return C;
}

matrix trans(matrix M) //矩阵转置
{
	uint8_t i, j;
	matrix C;
	C.row = M.col;
	C.col = M.row;
	C.mat = (double **)malloc(C.row * sizeof(double *));

	for (i = 0; i < C.row; i++)
	{
		C.mat[i] = (double *)malloc(C.col * sizeof(double));
		for (j = 0; j < C.col; j++)
		{
			C.mat[i][j] = M.mat[j][i];
		}
	}
	return C;
}

double trace(matrix M) //矩阵的迹
{
	if (M.row != M.col)
	{
		ERROR_Handler("Not square matrix!");
	}

	uint8_t i;
	double trace = 0.0;
	for (i = 0; i < M.row; i++) trace += M.mat[i][i];
	return trace;
}

//返回矩阵范数
double norm(matrix m, NORM_TYPE type)
{
	uint8_t i, j;
	double norm = 0.0, sum = 0.0;

	switch (type)
	{
	case NORM_TYPE_1:
		for (j = 0; j < m.col; j++)
		{
			sum = 0.0;
			for (i = 0; i < m.row; i++)
			{
				sum += fabs(m.mat[i][j]);
			}
			norm = __max(norm, sum);
		}
		return norm;

	case NORM_TYPE_INF:
		for (i = 0; i < m.row; i++)
		{
			sum = 0.0;
			for (j = 0; j < m.col; j++)
			{
				sum += fabs(m.mat[i][j]);
			}
			norm = __max(norm, sum);
		}
		return norm;

	case NORM_TYPE_FRO:
		for (i = 0; i < m.row; i++)
			for (j = 0; j < m.col; j++)
			{
				sum += m.mat[i][j] * m.mat[i][j];
			}
		return sqrt(sum);

	}
}

//返回矩阵的某种条件数
double cond(matrix M, NORM_TYPE type)
{
	return norm(M, type) * norm(inv(M), type);
}

vector jacobi(matrix A, vector b)
{
	if (A.row != A.col || A.row != b.len)
	{
		ERROR_Handler("size doesn't match!");
	}

/*
	matrix B;
	B.row = A.row, B.col = A.col;
	B.mat = (double**)malloc(B.row * sizeof(double*));

	for (uint8_t i = 0; i < B.row; i++)
	{
		B.mat[i] = (double*)malloc(B.col * sizeof(double));

		for (uint8_t j = 0; j < B.col; j++)
		{
			B.mat[i][j] = -A.mat[i][j] / A.mat[i][i];
		}
		B.mat[i][i] = 0.0;
	}

	
		mat_show(B);

		if(norm(B,NORM_TYPE_INF) >= 1.0)
		{
			ERROR_Handler("woops! This gonna take me forever!");
		}

		mat_delete(B);
*/

	vector x, temp;
	x.len = b.len; temp.len = b.len;

	x.vec = (double*)malloc(x.len * sizeof(double));
	temp.vec = (double*)malloc(temp.len * sizeof(double));

	memset(temp.vec, 0.0, x.len * sizeof(double));

	double norm;
	uint8_t count = 0;

	do
	{
		norm = 0.0;

		for (uint8_t i = 0; i < x.len; i++)
		{
			x.vec[i] = 0.0;

			for (uint8_t j = 0; j < x.len; j++)
			{
				x.vec[i] -= A.mat[i][j] * temp.vec[j];
			}

			x.vec[i] += A.mat[i][i] * temp.vec[i] + b.vec[i];
			x.vec[i] /= A.mat[i][i];

			norm += pow2(x.vec[i] - temp.vec[i]);
		}

		memcpy(temp.vec, x.vec, x.len * sizeof(double));

	} while (sqrt(norm) > EPS && count++ < 100);

	if (sqrt(norm) > EPS) puts("failed");

	free(temp.vec);
	return x;
}

vector gauss_seidel(matrix A, vector b)
{
	if (A.row != A.col || A.row != b.len)
	{
		ERROR_Handler("size doesn't match!");
	}


}
