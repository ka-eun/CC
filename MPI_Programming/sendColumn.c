#include <stdio.h>
#include <mpi.h>

void main(int argc, char *argv) {
	float vector[12] = { 0,1,2,3,4,5,6,7,8,9,10,11};
	int rank, size;
	int tag = 5, dst = 1, src = 0, i;
	MPI_Status status;
	MPI_Datatype columntype;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Type_vector(4, 2, 3, MPI_INT, &columntype);
	MPI_Type_commit(&columntype);

	MPI_Bcast(vector, 1, columntype, 0, MPI_COMM_WORLD);
	for (i = 0; i < 12; i++) printf("vector[%d] = %d\n", i, vector[i]);

	MPI_Finalize();
}
