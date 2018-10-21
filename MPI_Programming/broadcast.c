#include <stdio.h>
#include <mpi.h>

void main(int argc, char*argv[]) {
	int i, rank;
	int array[4];

	MPI_Init(&argc, &argv);
	MPI_Comm_rankg(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		for (i = 0; i < 4; i++) array[i] = i;
	}
	else {
		for (i = 0; i < 4; i++) array[i] = 0;
	}

	MPI_Bcast(array, 4, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 1) {
		for (i = 0; i < 4; i++) {
			printf("array[%d] = %d\n", i, array[i]);
		}
	}

	MPI_Finalize();
}
