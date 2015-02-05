#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void printVector(int size, double *vector)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf(" %lf ", vector[i]);
	}
	printf("\n");
}

double* generateVector(int size, double *vector)
{
	int counter = 0;
	double i;
	vector = malloc(size*sizeof(double));
	for (i = 1; i < size+1; i++)
	{
		//printf("%lf\n", 1 / (i*i));
		vector[counter] = 1 / (i*i);
		counter++;
	}
	return vector;
}

double computeSum(int size, double *vector)
{
	double sum;
	int i;
	for (i = 0; i < size; i++)
	{
		sum += vector[i];
		//printf("The sum so far: %lf\n", sum);
	}
	return sum;
}
double computeDifference(double sum)
{
	// We know the sum is supposed to be pi^2 / 6
	double actualSum = M_PI * M_PI / 6;
	return actualSum - sum; 
}

int main(int argc, char *argv[])
{
	// argv[] contains sizes of the vectors to be generated
	int counter = 1;
	int n;
	double *vector;
	if (argc == 0)
	{
		printf("Error no vector size has been given in commandline \n");
		exit(0);
	}
	while (counter < argc)
	{
		n = pow(2.0, atoi(argv[counter]));
		printf("The size of generated vector: %d\n", n);
		// The vector is v(i) = 1/i^2
		// following generates a vector
		double actualSum = M_PI * M_PI / 6;
		vector = generateVector(n, vector);
		double sum = computeSum(n, vector);
		//printVector(n, vector);

		printf("the sum of all vector elements: %lf\n", sum);
		printf("the actual sum as vector size goes -> inf: %lf\n", actualSum);
		printf("The difference for, %d elements is: %lf\n", n, computeDifference(sum));
		printf("\n");
		counter++;
	}


	return 0;
}