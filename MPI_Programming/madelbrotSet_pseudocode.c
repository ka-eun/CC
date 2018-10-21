#include <stdio.h>
#include <mpi.h>

main() {
	x = -1; y = -1; color = -1;

	if (rank == 0) {
		for (i = 0; i < 10; i++) {
			for (j = 0; j < 10; j++) {
				MPI_Recv(Request_from_processes, x, y, color);
				MPI_Send(Work_for_processes);
				if (x != -1) screen[x][y] = color;
			}
		}

		for (i = 0; i < size; i++) {
			MPI_Recv(Request_from_processes, x, y, color);
			screen[x][y] = color;
			MPI_Send((-1, -1)); // (-1,-1) means 'work is over'
		}
	}
	else {
		while (1) {
			MPI_Send(x, y, color to process0);
			MPI_Recv(x, y in work from process0);
			if (x != -1) color = f(x, y);
			else break; //work is over
		}
	}

}
