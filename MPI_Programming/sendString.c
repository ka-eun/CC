#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(void) {

	char greeting[100];
	int my_rank;
	int comm_size;
	int source;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	
	if (my_rank != 0) {
		sprintf(greeting, "Greetings from process %d of %d!\n", my_rank, comm_size);
		MPI_Send(greeting, strlen(greeting) + 1, MPI_CHAR, 0, 5, MPI_COMM_WORLD);
	}
	else {
		printf("Greetings from process %d of %d!\n", my_rank, comm_size);
		for (source = 1; source < comm_size; source++) {
			MPI_Recv(greeting, 100, MPI_CHAR, source, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("%s\n", greeting);
		}
	}

	MPI_Finalize();
	return 0;
}
