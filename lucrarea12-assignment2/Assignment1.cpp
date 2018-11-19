#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
	
	int my_rank;
	int p;
	int a[256] = {};
	int b[256] = {};
	int i; 
	int x = 0;
	MPI_Datatype my_type;
	

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	int work_flow = 1000 / (p-1);
	

	if (my_rank == 0)
	{
		for (int i = 1; i <= p-1; i++) 
		{
			MPI_Send(&work_flow, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}

		for (int i = 1; i <= p-1; i++)
		{
			MPI_Recv(&a, 256, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			for (int j = 0; j <= 255; j++) 
			{
				b[j]+= a[j];
			}
		}

		for (int j = 0; j <= 255; j++) 
		{
			printf("j = %d %d\n",j,b[j]);
		}
	}


	if (my_rank != 0)
	{
		int work_flow;
		MPI_Recv(&work_flow, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		FILE* file = fopen("inputa.txt", "r");
		int buf;

		//for positioning in the file
		for (int i = 0; i < (my_rank - 1)* work_flow; i++) 
		{
			fscanf(file, "%d", &buf);
		}


		if (my_rank < p-1) 
		{
			for (int i = (my_rank - 1)* work_flow; i < my_rank * work_flow; i++) 
			{
				fscanf(file, "%d", &buf);
				a[buf]++;
			}
		}else 
		{
			while (fscanf(file, "%d", &buf) != EOF) 
			{
				a[buf]++;
			}
		}

		MPI_Send(&a, 256, MPI_INT, 0, 0, MPI_COMM_WORLD);

			

	}

	
	MPI_Finalize();
	return 0;
}