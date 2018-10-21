#include <stdio.h>
#include <mpi.h>

double trap(double, double, int, double);
double f(double x);
void get_data(int, int, double*, double*, int*);

int main() {
	int rank, size, n, local_n;
	double a, b, h, local_a, local_b;
	double local_int, total_int;
	int source;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	get_data(rank, size, &a, &b, &n);
	h = (b - a) / n;
	local_n = n / size;
	local_a = a + rank * local_n * h;
	local_b = local_a + local_n * h;
	local_int = trap(local_a, local_b, local_n, h);

	if (rank != 0) {
		MPI_Send(&local_int, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	else {
		total_int = local_int;
		for (source = 1; source < size; source++) {
			MPI_Recv(&local_int, 1, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			total_int += local_int;
		}

		printf("Integral from %.2f to %.2f = %.2f  with %d trapezoids\n", a, b, total_int, n);
	}

	MPI_Finalize();
	return 0;
}

void get_data(int rank, int size, double *a, double *b, int *n) {
	int dst;
	if (rank == 0) {
		print("Enter a, b, and n : ");
		fflush(stdout);
		scanf("%f %f %d", a, b, n);
		for (dst = 1; dst < size; dst++) {
			MPI_Send(a, 1, MPI_DOUBLE, dst, 0, MPI_COMM_WORLD);
			MPI_Send(b, 1, MPI_DOUBLE, dst, 0, MPI_COMM_WORLD);
			MPI_Send(n, 1, MPI_INT, dst, 0, MPI_COMM_WORLD);
		}
	}
	else {
		MPI_Recv(a, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(b, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
}

double f(double x) {
	return x * x + 5;
}

double trap(double left, double right, int trap_count, double width) {
	double estimate, x;
	int i;

	estimate = (f(left) + f(right)) / 2.0;
	for (i = 1; i <= trap_count; i++) {
		x = left + i * width;
	}
	estimate *= x;
	return estimate;
}
