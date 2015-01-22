#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char **argv)
{
	int rank, size, tag, i;
	MPI_Status status;
	char message[20]; /* Creates char message to contain "hello world"*/

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
/*	printf("size %d \n", size);
	printf("rank %d \n", rank); */
	tag = 100;
	if (rank == 0)
	{
		/*printf("something\n");*/
		strcpy(message, "Hello, world");
		for (i=1; i < size; i++)
		{
			MPI_Send(message, 13, MPI_CHAR, i, tag, MPI_COMM_WORLD);
		}
	}
	else
	{
		/*printf("something dark\n");*/
		MPI_Recv(message, 13, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
	}
	printf("process %d: %s\n", rank, message);
	MPI_Finalize();
	return 0;
}

/*To Compile with more than 1 processor,  mpirun -np 4 ./hello */