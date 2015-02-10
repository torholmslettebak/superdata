#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>
/*#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_num_threads() 0
    #define omp_get_thread_num() 0
#endif
*/

void printVector(int size, double *vector)
{
	printf("Here comes the vector\n");
	int i;
	for (i = 0; i < size; i++)
	{
		printf(" %lf ", vector[i]);
	}
	printf("\n");
}
double myf(double x)
{
  return 1.0/(x*x*1.0);
}

double WallTime ()
{
#ifdef HAVE_MPI
  return MPI_Wtime();
#elif defined(HAVE_OPENMP)
  return omp_get_wtime();
#else
  struct timeval tmpTime;
  gettimeofday(&tmpTime,NULL);
  return tmpTime.tv_sec + tmpTime.tv_usec/1.0e6;
#endif
}

double* generateVector(int size, double *vector)
{
	int i;
	vector = malloc(size*sizeof(double));
	#pragma omp parallel \
	shared (size) \
	private (i)
	#pragma omp for schedule(static) 
	for (i = 0; i < size; i++)
	{
		#pragma omp critical //
		vector[i] = (double) (1 / (i+1)*(i+1));
	}
	return vector;
}

double* generateVector2(int size, double *vector)
{
	int counter = 0;
	int i, thread_id;
	vector = malloc(size*sizeof(double));

	return vector;
}


double computeSum(int size, double *vector)
{
	int i;
	double sum;
	#pragma omp parallel for reduction(+:sum) schedule(static)
	for (i = 0; i < size; i++)
	{
		sum += vector[i];
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
	printf ( "  Number of processors available = %d\n", omp_get_num_procs ( ) );
	printf ( "  Number of threads =              %d\n", omp_get_max_threads ( ) );
	int counter = 1;
	int n, i;
	double *vector, t1, t2, dt;
	t1 = WallTime();
	int num_threads, thread_id;
	if (argc == 0)
	{
		printf("Error no vector size has been given in commandline \n");
		exit(0);
	}
	/*Går gjenom argv og kjører metoder ut fra argv*/
	for (i = 1; i < argc; i++)
	{

		n = pow(2.0, atoi(argv[i]));
		// The vector is v(i) = 1/i^2
		// following generates a vector
		double actualSum = M_PI * M_PI / 6;
		vector = generateVector(n, vector);
		double sum = computeSum(n, vector);
		

		printf("the sum of all vector elements: %lf\n", sum);
		printf("the actual sum as vector size goes -> inf: %lf\n", actualSum);
		printf("The difference for, %d elements is: %lf\n", n, computeDifference(sum));

	}
	t2 = WallTime();
  	dt = t2 - t1;
	printf("the program, with generating and summing (WTIH OMP) took: %lf seconds\n", dt );

	return 0;
}