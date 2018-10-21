#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(void) {

	int rank, size;
	int a, i;
	int tag = 5;
	MPI_Status status;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank != 0) {
		a = rank;
		MPI_Send(&a, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
	}
	else if (rank == 0) {
		for (i = 1; i < size; i++) {
			MPI_Recv(&a, 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
			pritnf("a = %d, source = %d\n", a, status.MPI_SOURCE);
		}
	}

	MPI_Finalize();
	return 0;

}
