#include <stdio.h>
#include "stdafx.h"
#include "mpi.h"

int main(int argc, char* argv[])
{
	FILE* file = fopen("inputa.txt", "r");

	int my_rank;
	int p;	
	int c[1000];
	
	int i;
	int x = 0;
	MPI_Datatype my_type;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);


	
	for (i = 0; i<999; i++)
		c[i] = 0;


	if (my_rank == 0)
	{
		for (i = 0; i < 333; i++)
		{
			fscanf(file, "%d", &x);
			MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		}
			

		for (i = 334; i < 666; i++)
		{
			fscanf(file, "%d", &x);
			MPI_Send(&x, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
		
		}
			

		for (i = 667; i < 1000; i++)
		{
			fscanf(file, "%d", &x);
			MPI_Send(&x, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
		}
			
	}


	if (my_rank != 0)
	{
		for (i = 0; i<333; i++)
		{
			MPI_Recv(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			c[i] = x;
		}

		for (i = 334; i<666; i++)
		{
			MPI_Recv(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			c[i] = x;
		}

		for (i = 667; i<1000; i++)
		{
			MPI_Recv(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			c[i] = x;
		}

	}

	for (int i = 0; i < 1000; i++)
	{
		printf("c[%d] = %d\n", i, c[i]);
	}

	MPI_Finalize();
	return 0;
}