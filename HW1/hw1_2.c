#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#define MAX 1000

int main(void) {
	int a[MAX]; /* Array for Integer */
	int b[MAX] = { 0 };
	int my_rank; /* my process rank */
	int comm_sz; /* number of processes */
	int i = 0, j=0; /* iteration loop variable */
	int x; /* for range of devided array */
	int local_sum = 0;
	int local_sum_array[MAX] = { 0 };
	

	srand(time(NULL));

	MPI_Init(NULL, NULL); /* initialize variables */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); /* allocate each process numbers */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); /* allocate size to comm_sz */

	if (my_rank == 0) {
		for (i = 0; i < MAX; i++) {
			a[i] = i;
			// a[i] = rand()%1000; /* allocate random integer around 0~999 */
		}
		MPI_Scatter(&a, MAX, MPI_INT, &a, MAX, MPI_INT, 0, MPI_COMM_WORLD);
	}

	x = MAX / comm_sz;

	for (i = 0; i <x; i++) {
		local_sum += a[i];
	}

	MPI_Allgather(&local_sum, comm_sz, MPI_INT, &local_sum_array, comm_sz, MPI_INT, MPI_COMM_WORLD);

	for (i = 0; i < x; i++) {
		b[i] = 0;
		for (j = 0; j < i; j++) b[i] += a[j];
		for (j = 0; j < my_rank; j++) b[i] += local_sum_array[j];
	}

	MPI_Gather(&b, x, MPI_INT, &b, x, MPI_INT, 0, MPI_COMM_WORLD);

	if (my_rank == 0) {
		for (i = 0; i < MAX; i++) printf("%d ", b[i]);
		printf("\n");
	}

	MPI_Finalize();
	return 0;

}

