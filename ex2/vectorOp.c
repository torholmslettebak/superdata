
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
/* Implement a program in C/Fortran which performs the following operations:
x = a + γb
y = a + Ab 
α = x^T y */


double randZeroToOne(void);
double **vectorMatrix; /*column 1 is vector a, column 2 is vector b, and the entire matrix is Matrix A*/
double *xVector, *yVector, *resultMatMult;

double randZeroToOne()
{
	double r = rand() / (RAND_MAX + 1.);
    return r*10;
}

void fillVectors()
{
	int i, j;
	vectorMatrix = malloc(3 * sizeof(double));
	for (i = 0; i < 3; i++)
	{
		vectorMatrix[i] = malloc(3 * sizeof(double));
		
		vectorMatrix[i][0] = randZeroToOne();
		vectorMatrix[i][1] = randZeroToOne();
		vectorMatrix[i][2] = randZeroToOne();
	}
}

void matrixVectorProduct(double **Matrix)
{
	int systemSize = 3;
	resultMatMult = malloc(systemSize * sizeof(double));
	printf("System size %d\n", systemSize );
	int i, j;
	for (i = 0; i < systemSize; i ++)
	{
		for (j = 0; j < systemSize; j++)
		{
			resultMatMult[i] += vectorMatrix[i][j] * vectorMatrix[j][1];
		}
	}
}

void operation1(double gamma)
{
	int i;
	xVector = malloc(3*sizeof(double));
	for (i=0; i < 3; i++)
	{
		xVector[i] = vectorMatrix[i][0] + gamma*vectorMatrix[i][1];
	}
}

void operation2()
{
	yVector = malloc(3 * sizeof(double));
	int i, j;
	matrixVectorProduct(vectorMatrix);
	for (i = 0; i < 3; i++)
	{
		yVector[i] = vectorMatrix[i][0] + resultMatMult[i];
	}

}
double operation3()
{
	int i;
	double alpha;
	for(i = 0; i < 3; i++)
	{
		alpha += xVector[i]*yVector[i];
	}
	return alpha;	
}


void printMatrix(int n, int m, double **matrix)
{
	int row, col;
	for (row = 0; row < n; row++)
	{
		for (col = 0; col < m; col++)
		{
			printf(" %lf ", vectorMatrix[row][col]);
		}
		printf("\n");
	}
	
}
void printVector(int size, double *vector)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf(" %lf \n", vector[i]);
	}
}

void main()
{
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	unsigned int iseed = (unsigned int)time(NULL);
	srand (iseed);
	double gamma;
	printf("Type a scalar double gamma (e.g. 1.02): \n");
	scanf("%lf", &gamma);
	printf("Your gamma is : %lf\n", gamma);
	fillVectors();
	operation1(gamma);
	printMatrix(3, 3, vectorMatrix);
	printf("\n");
	printf("Vector x from operation1: \n");
	printVector(3, xVector);
	printf("\n");
	operation2();
	printf("the result of Ab: \n");
	printVector(3, resultMatMult);
	printf("Vector y from operation2: \n");
	printVector(3, yVector);
	printf("alpha = %lf\n", operation3());
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("CPU time used %lf \n", cpu_time_used);
}
