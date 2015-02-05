#include <stdio.h>	/* required for file operations */
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
/*#include <conio.h>*/  /* for clrscr, clrscr clears the screen amd move the cursor to upper left hand corner of screen.*/
/*#include <dos.h> */ /* for delay */
/* C program which calculates y = Ax */
/*inputEx1.txt contains the matrices, the programs reads it, no matter size and so on*/
double **Amatrix, *xVector, *yVector;
int systemSize;

void read()
{
	int lineNumber = 6; /* The line where program begins to read*/
	int count = 0;
	FILE *file; /* Declares file pointer*/
	file = fopen ("inputEx1.txt", "r"); /* opens file for reading*/
	char line[256];
	char temp[100];
	if (file != NULL)
	{
		int i, j;
		for ( i = 0; i < 5; i++)
		{
			fgets(line, sizeof line, file); /*Reads the description of input*/
		}
		fscanf(file, "%d", &systemSize); /* reads and find system size*/

		Amatrix = malloc(systemSize * sizeof(double*));
		for (i = 0; i < systemSize; i++)
		{
			Amatrix[i] = malloc(systemSize * sizeof(double));
			for (j = 0; j < systemSize; j++)
			{
				fscanf(file, "%lf", &Amatrix[i][j]);
			}
		}
		xVector = malloc(systemSize * sizeof(double));
		for (i = 0; i < systemSize; i++)
		{
			fscanf(file, "%lf", &xVector[i]);
		}


	}
	fclose(file);
}

void matrixVectorProduct()
{
	yVector = malloc(systemSize * sizeof(double));
	int i, j;
	for (i = 0; i < systemSize; i ++)
	{

		for (j = 0; j < systemSize; j++)
		{
			yVector[i] += Amatrix[i][j] * xVector[j];
		}
	}

}

int main(int argc, char *argv[])
{
	read();
	matrixVectorProduct();
	printf("yVector %lf %lf %lf\n", yVector[0], yVector[1], yVector[2]);
}
