#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char argv[]){
	double global_result = 0.0;
	thread_count = strtol(argv[1], NULL, 10);
	a, b, n 입력받음;
#pragma omp parallel num_threads(thread_count);
	Trap(a, b, n, &global_result);
	global_result 출력;
	return 0;
	}

void Trap(double a, double b, int n, double *global_result){
	int my_rank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();
	local하게 맡은 구역 계산;
#pragma omp critical
	*global_result += my_result;
	}
