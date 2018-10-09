#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#define MAX 1000

int main(void) {
	int a[MAX]; /* Array for Integer */
	int my_rank; /* my process rank */
	int comm_sz; /* number of processes */
	int i = 0; /* iteration loop variable */
	int x, high, low; /* for range of devided array */
	int local_sum = 0;
	int global_sum = 0;

	srand(time(NULL));

	MPI_Init(NULL, NULL); /* initialize variables */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); /* allocate each process numbers */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); /* allocate size to comm_sz */

	if (my_rank==0) {
		for (i = 0; i < MAX; i++) {
			a[i] = i;
			// a[i] = rand()%1000; /* allocate random integer around 0~999 */
		}
		for (i = 1; i < comm_sz; i++) {
			MPI_Send(&a, MAX, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
	}
	else {
		MPI_Recv(&a, MAX, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}


	x = MAX / comm_sz;
	low = my_rank * x;
	high = low + x;

	for (i = low; i < high; i++) {
		if (a[i] % 2 == 1) local_sum += a[i];
	}

	if (my_rank != 0) {
		MPI_Send(&local_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	else {
		for (int i = 1; i < comm_sz; i++) {
			MPI_Recv(&local_sum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			global_sum += local_sum;
		}

		printf("SUM = %d\n", global_sum);
	}

	MPI_Finalize();
	return 0;

}

