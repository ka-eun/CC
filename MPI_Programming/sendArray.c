#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(void) {

	int a[10], b[10], count, my_rank, size, i, j;
	MPI_Status status;
	
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank != 0) {
		for (i = 1; i < my_rank; i++) {
			a[i] = 10 + my_rank;
		}
		MPI_Send(a, my_rank, MPI_INT, 0, tag, MPI_COMM_WORLD);

	}
	else {
		for (i = 1; i < size; i++) {
			MPI_Recv(b, 10, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			printf("souce = %d", status.MPI_SOURCE);
			MPI_Get_count(&status, MPI_INT, &count);
			for (j = 0; j < count; j++) {
				printf("%d  ", b[i]);
			}
			printf("\n");
		}
	}

	MPI_Finalize();
	return 0;

}
