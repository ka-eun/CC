#include <stdio.h>
#include <mpi.h>

void main(int argc, char *argv) {
	int root = 0;
	char buffer[100];
	int rank, size;
	float *a;
	float *b;
	int *n;
	int pos;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		printf("Enter a, b, n : ");
		fflush(stdout);
		scanf("%f, %f, %d", a, b, n);

		pos = 0;
		MPI_Pack(a, 1, MPI_FLOAT, buffer, 100, &p, MPI_COMM_WORLD);
		MPI_Pack(b, 1, MPI_FLOAT, buffer, 100, &p, MPI_COMM_WORLD);
		MPI_Pack(n, 1, MPI_INT, buffer, 100, &p, MPI_COMM_WORLD);
	}

	MPI_Bcast(buffer, 100, MPI_PACKED, root, MPI_COMM_WORLD);

	else{
		pos = 0;
		MPI_Unpack(buffer, 100, &p, a, 1, MPI_FLOAT, MPI_COMM_WORLD);
		MPI_Unpack(buffer, 100, &p, b, 1, MPI_FLOAT, MPI_COMM_WORLD);
		MPI_Unpack(buffer, 100, &p, n, 1, MPI_INT, MPI_COMM_WORLD);
	}


	MPI_Finalize();
}
