#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(void) {

	int num, array[5], source[10];
	int rank, size;
	int tag = 5, i;
	MPI_Status status;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank != 0) {
		num = 10 + rank;
		MPI_Send(&num, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
	}
	else {
		for (i = 0; i < size - 1; i++) {
			MPI_Recv(array + i, 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
			source[i] = status.MPI_SOURCE;
		}
		for (i = 0; i < size - 1; i++) {
			printf("array[%d] = %d\n", source[i], array[i]);
		}
	}

	MPI_Finalize();
	return 0;

}
