#include <stdio.h>
#include <mpi.h>

void main(int argc, char *argv) {
	float vector[10] = { 0,1,2,3,4,5,6,7,8,9 };
	int rank, size;
	int tag = 5, count = 3, dst = 1, src = 0, i;
	MPI_Status status;
	MPI_Dataytype row_type;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Type_contiguous(3, MPI_FLOAT, &row_type);
	MPI_Type_commit(&row_type);

	if (rank == 0) {
		MPI_Send(vector + 2, 1, row_type, dst, tag, MPI_COMM_WORLD);
	}
	else if (rank==1){
		MPI_Recv(vector, 1, row_type, src, tag, MPI_COMM_WORLD, &status);
		for (i = 0; i < count; i++) {
			prinf("%.2f ", vector[i]);
		}
	}

	MPI_Finalize();
}
