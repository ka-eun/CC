#include <stdio.h>
#include <mpi.h>

typedef struct {
	int size;
	MPI_Comm comm;
	MPI_Comm row_comm;
	MPI_Comm column_comm;
	int order;
	int my_row;
	int my_column;
	int my_rank;
} GRID_TYPE;

void setup_grid(GRID_TYPE* grid) {
	int old_rank;
	int dimensions[2];
	int periods[2];
	int coordinates[2];
	int varing_coordinates[2];
	
	MPI_Comm_size(MPI_COMM_WORLD, &(grid->size));
	MPI_Comm_rank(MPI_COMM_WORLD, &old_rank);
	grid->order = (int)sqrt((double)grid->size);
	dimensions[0] = dimensions[1] = grid->order;
	periods[0] = periods[1] = 1;

	MPI_Cart_create(MPI_COMM_WORLD, 2, dimensions, periods, 1, &(gid->comm));
	MPI_Comm_rank(grid->comm, &(grid->my_rank));
	MPI_Cart_coords(grid->comm, grid->my_rank, 2, coordinates);
	grid->my_row = coordinates[0];
	grid->my_column = coordinates[1];

	varing_coords[0] = 0; varing_coords[1] = 1;
	MPI_Cart_sub(grid->comm, varing_coords, &(grid->row_comm));
	varing_coords[0] = 1; varing_coords[1] = 0;
	MPI_Cart_sub(grid->comm, varing_coords, &(grid->column_comm));
}

void Fox(int n, GRID_TYPE* grid, LOCAL_MATRIX_TYPE* local_A, LOCAL_MATRIX_TYPE* local_B, LOCAL_MATRIX_TYPE* local_C) {
	int step;
	int bcast_root;
	int n_bar;
	int src;
	int dst;
	int tag = 10;
	MPI_Status status;

	n_bar = n / grid->order;
	Set_to_zero(local_C);

	/* Circular shift of matrix B */
	src = (grid->my_row + 1) % (grid->order);
	dst = (grid->my_row + grid->order - 1) % (grid->order); 

	/* for broadcasting block of matrix A */
	temp_A = Local_marix_allocate(n_bar);

	for (step = 0; step < grid->order; step++) {
		bcast_root = (grid->my_row + step) % (grid->order);
		if (bcast_root == grid->my_rank) {
			MPI_Bcast(local_A, 1, DERIVED_LOCAL_MATRIX, bcast_root, grid->row_comm);
			Local_matrix_multiply(local_A, local_B, local_C);
		}
		else {
			MPI_Bcast(temp_A, 1, DERIVED_LOCAL_MATRIX, bcast_root, grid->row_comm);
			Local_matrix_multiply(local_A, local_B, local_C);
		}

		MPI_Send(local_B, 1, DERIVED_LOCAL_MATRIX, dst, tag, grid->column_comm);
		MPI_Recv(local_B, 1, DERIVED_LOCAL_MATRIX, src, tag, grid->row_comm, &status);
	}
}
