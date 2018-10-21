#include <stdio.h>
#include <mpi.h>

void main(int argc, char*argv[]) {

	int rank, size;
	int data[100], i, x, low, high, local_result, result;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		for (i = 0; i < 100; i++) data[i] = i;
	}

	MPI_Bcast(data, 100, MPI_INT, 0, MPI_COMM_WORLD);
	
	x = 100 / size;
	low = rank * x;
	high = low + x;
	local_result = 0;

	for (i = low; i < high; i++) local_result += data[i];

	MPI_Reduce(&local_result, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0) printf("The sum is %d\n", result);
	
	MPI_Finalize();

}
