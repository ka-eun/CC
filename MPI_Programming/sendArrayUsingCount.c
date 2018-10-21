#include <stdio.h>
#include <mpi.h>

void main(int argc, char *argv) {
	float vector[10] = { 0,1,2,3,4,5,6,7,8,9 };
	int rank, size;
	int tag = 5, count = 3, dst = 1, src = 0, i;
	MPI_Status status;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		MPI_Send(vector + 2, count, MPI_FLOAT, dst, tag, MPI_COMM_WORLD);
	}
	else if (rank==1){
		MPI_Recv(vector, count, MPI_FLOAT, src, tag, MPI_COMM_WORLD, &status);
		for (i = 0; i < count; i++) {
			prinf("%.2f ", vector[i]);
		}
	}

	MPI_Finalize();
}
