/*
Compute the input scores with shared variable:
Using Pthread-Semaphore
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#pragma warning(disable:4996)

int thread_count;  // number of threads
int task_size; // number of scores which each threads compute
sem_t semaphore; // semaphore for critical section

// number of student in each score range
int count0_10 = 0; 
int count11_20 = 0;
int count21_30 = 0;
int count31_40 = 0;
int count41_50 = 0;
int count51_60 = 0;
int count61_70 = 0;
int count71_80 = 0;
int count81_90 = 0;
int count91_100 = 0;

void *Count(void *rank); // function to compute the student numbers in each score range and update to shared variable


int main(int argc, char *argv[]) {
    long thread;
    sem_init(&semaphore, 0, 1); // initailize semaphore
    pthread_t * thread_handles;

    thread_count = strtol(argv[1], NULL, 10); // number of threads
    thread_handles = malloc(thread_count * sizeof(pthread_t)); // handler of threads  
    task_size = (int)100000 / thread_count; // number of scores that each threads will manage 

    // create theads and assign to handlers. Each threads will run function Count()
    for (thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, Count, (void*)thread);
    }

    // destroy each threads
    for (thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);

    // print the number of students in each sore range in main thread 
    printf("0 - 10 : %d\n", count0_10);
    printf("11 - 20 : %d\n", count11_20);
    printf("21 - 30 : %d\n", count21_30);
    printf("31 - 40 : %d\n", count31_40);
    printf("41 - 50 : %d\n", count41_50);
    printf("51 - 60 : %d\n", count51_60);
    printf("61 - 70 : %d\n", count61_70);
    printf("71 - 80 : %d\n", count71_80);
    printf("81 - 90 : %d\n", count81_90);
    printf("91 - 100 : %d\n", count91_100);

    return 0;
}


void *Count(void *rank) {
     // Each thread has its rank, task size and value for range of its task 
    long my_rank = (long)rank;
    int my_first_score = my_rank * task_size ;
    int my_last_score = (my_rank+1) * task_size - 1;

    // read scores from scores.txt and store it to arry score 
    FILE *fp = fopen("scores.txt", "r"); 
    int score[100000]; 
    int buffer;
    for (int i = 0; i < 100000; i++) {
        fscanf(fp, "%d", &buffer);
        score[i] = buffer;
    }
    fclose(fp);
    
    // number of student in each score range
    int local_count0_10 = 0; 
    int local_count11_20 = 0;
    int local_count21_30 = 0;
    int local_count31_40 = 0;
    int local_count41_50 = 0;
    int local_count51_60 = 0;
    int local_count61_70 = 0;
    int local_count71_80 = 0;
    int local_count81_90 = 0;
    int local_count91_100 = 0;

    // For each range of task, each thread computes the count for score range 
    for (int i = my_first_score; i <= my_last_score; i++) {
        if (score[i] < 11) local_count0_10++;
        else if (10 < score[i] && score[i] < 21) local_count11_20++;
        else if (20 < score[i] && score[i] < 31) local_count21_30++;
        else if (30 < score[i] && score[i] < 41) local_count31_40++;
        else if (40 < score[i] && score[i] < 51) local_count41_50++;
        else if (50 < score[i] && score[i] < 61) local_count51_60++;
        else if (60 < score[i] && score[i] < 71) local_count61_70++;
        else if (70 < score[i] && score[i] < 81) local_count71_80++;
        else if (80 < score[i] && score[i] < 91) local_count81_90++;
        else local_count91_100++;
    }

    // sum to shared variable in critical section. 
     sem_wait(&semaphore);  
    count0_10 += local_count0_10;
    count11_20 += local_count11_20;
    count21_30 += local_count21_30;
    count31_40 += local_count31_40;
    count41_50 += local_count41_50;
    count51_60 += local_count51_60;
    count61_70 += local_count61_70;
    count71_80 += local_count71_80;
    count81_90 += local_count81_90;
    count91_100 += local_count91_100;
    sem_post(&semaphore);     

    return NULL;
} 
