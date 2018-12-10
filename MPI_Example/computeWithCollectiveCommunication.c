/* 
MPI Programming

Process P0 has array a[1000] with arbitrary integer numbers.
This program compute prefix sum of the numbers with multiple processes and collective communication.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#define MAX 1000

int main(void) {
	int a[MAX]; /* Array for Integer */
	int buffer[MAX]; /* array for devided a[] */
	int b[MAX]; /* final array of prefixsum in process0 */
	int result[MAX]; /* array of local prefix_sum in each process */
	int my_rank; /* my process rank */
	int comm_sz; /* number of processes */
	int i = 0, j = 0; /* iteration loop variable */
	int x; /* for range of devided array */
	int local_sum = 0; /* local sum of local_prefixsum array in each process */
	int local_sum_array[MAX] = { 0 }; /* array of local_sum gathered from all porcess */


	srand(time(NULL));

	MPI_Init(NULL, NULL); /* initialize variables */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); /* allocate each process numbers */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); /* allocate size to comm_sz */

	x = MAX / comm_sz;

	if (my_rank == 0) {

		/* allocate random integer around 0~999 */
		for (i = 0; i < MAX; i++) {
			// a[i] = i;
			a[i] = rand()%1000; 
		}
	}

	/* scatter array a[] to all process */
	MPI_Scatter(&a, x, MPI_INT, &buffer, x, MPI_INT, 0, MPI_COMM_WORLD);

	/* compute local_sum in each process */
	for (i = 0; i < x; i++) {
		local_sum += buffer[i];
	}

	/* all process gets the local_sum of each process and store in local_sum_array */
	MPI_Allgather(&local_sum, 1, MPI_INT, &local_sum_array, 1, MPI_INT, MPI_COMM_WORLD);

	/* compute the prefix sum withe divided a[] in each process */
	for (i = 0; i < x; i++) {
		result[i] = 0;
		for (j = 0; j <= i; j++) result[i] += buffer[j];
	}

	/* add the local_sum value to each prefix sum in all each process */
	for (j = 0; j < my_rank; j++) {
		for (i = 0; i < x; i++) result[i] += local_sum_array[j];
	}

	/* gather the computed prefix sum from each process to process 0 */
	MPI_Gather(&result, x, MPI_INT, &b, x, MPI_INT, 0, MPI_COMM_WORLD);

	/* print the final prefix sum in process 0 */
	if (my_rank == 0) {
		for (i = 0; i < MAX; i++) printf("%d ", b[i]);
		printf("\n");
	}

	MPI_Finalize();
	return 0;

}


