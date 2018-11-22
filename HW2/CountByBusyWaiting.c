#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#pragma warning(disable:4996)

int thread_count; // 쓰레드의 개수
int task_size; // 한 쓰레드가 맡아서 처리할 score의 개수
int flag;

// 10개의 score 구간에 속하는 학생 수를 global 변수 10개로 선언
int count0_10; 
int count11_20;
int count21_30;
int count31_40;
int count41_50;
int count51_60;
int count61_70;
int count71_80;
int count81_90;
int count91_100;

void *Count(void *rank); // 각 score구간에 속하는 학생 수를 계산하고 업데이트하는 함수


int main(int argc, char *argv[]) {
	long thread;
	pthread_t * thread_handles;

	thread_count = strtol(argv[1], NULL, 10); // 쓰레드의 개수
	thread_handles = malloc(thread_count * sizeof([pthread_t])); // 쓰레드가 할당될 thread_handles 선언
	task_size = (int)100 / thread_count;  // 각 쓰레드가 처리할 score개수
	flag = 0; // Busy waiting을 위해 사용되는 flag값을 0으로 초기화

	// 쓰레드의 개수만큼 쓰레드를 생성함. 각 쓰레드는 thread_handles에 할당되고 Count함수를 실행
	for (thread = 0; thread < thread_count; thread++) {
		pthread_create(&thread_handles[thread], NULL, Count, (void*)thread);
	}

	// main쓰레드에서 각 점수대별로 count된 수를 출력
	printf("0 - 10 : %d\n", count0_10);
	printf("0 - 10 : %d\n", count11_20);
	printf("0 - 10 : %d\n", count21_30);
	printf("0 - 10 : %d\n", count31_40);
	printf("0 - 10 : %d\n", count41_50);
	printf("0 - 10 : %d\n", count51_60);
	printf("0 - 10 : %d\n", count61_70);
	printf("0 - 10 : %d\n", count71_80);
	printf("0 - 10 : %d\n", count81_90);
	printf("0 - 10 : %d\n", count91_100);

	// 각 쓰레드를 없앰
	for (thread = 0; thread < thread_count; thread++) {
		pthread_join(thread_handles[thread], NULL);
	}

	free(thread_handles);
	return 0;
}


void *Count(void *rank) {
	// 각 쓰레드의 rank와 task_size 크기만큼의 처리할 score의 첫번째 순서값, 마지막 순서값 선언
	long my_rank = (long)rank;
	int my_first_score = my_rank * task_size ;
	int my_last_score = (my_rank+1) * task_size - 1;

	// scores.txt로부터 score를 읽어와 int형 score배열에 저장
	FILE *fp = fopen("scores.txt", "r"); 
	int score[100]; 
	int buffer;
	for (int i = 0; i < 100; i++) {
		fscanf(fp, "%d", &buffer);
		score[i] = buffer;
	}
	fclose(fp);

	// flag 값과 my_rank값이 같을때에만 공유변수인 각 점수대별 count를 업데이트함
	while (flag != my_rank);

	// 각 쓰레드가 맡아 처리할 score개수만큼 loop를 돌면서 점수대별 count를 계산
	for (int i = my_first_score; i <= my_last_score; i++) {
		if (score[i] < 11) count0_10++;
		else if (10 < score[i] && score[i] < 21) count11_20++;
		else if (20 < score[i] && score[i] < 31) count21_30++;
		else if (30 < score[i] && score[i] < 41) count31_40++;
		else if (40 < score[i] && score[i] < 51) count41_50++;
		else if (50 < score[i] && score[i] < 61) count51_60++;
		else if (60 < score[i] && score[i] < 71) count61_70++;
		else if (70 < score[i] && score[i] < 81) count71_80++;
		else if (80 < score[i] && score[i] < 91) count81_90++;
		else count91_100++;
	}

	// 할 일이 끝나면 flag값을 업데이트
	flag = (flag + 1) % thread_count;
	
	return NULL;
}
