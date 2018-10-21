#include <stdio.h>
#include <mpi.h>

void main(int argc, char*argv[]) {

	int i, size, rank;
	int isend, irecv[4];

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	isend = rank + 10;
	MPI_Gather(&isend, 1, MPI_INT, irecv, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		for (i = 0; i < 4; i++) {
			printf("irecv = %d", irecv[i]);
		}
	}

	MPI_Finalize();

}
