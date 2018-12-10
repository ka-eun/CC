#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void Hello(void);
int main(int argc, char argv[]){
	int thread_count  = strtol(argv[1], NULL, 10);

#pragma omp parallel num_threads(thread_count);  
	Hello();
	return 0;
	)

void Hello(){
	int my_rank = omp_get_thread_num(); // thread number (rank)
	int thread_count = omp_get_num_threads(); // number of threads
	printf(“Hello from %d of %d”, my_rank, thread_count);
	}
