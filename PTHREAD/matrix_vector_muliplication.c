void *Pth_mat_vect(void *rank){
	long my_rank = (long)rank;
	int i, j;
	int my_first_row=my_rank * local_m;
	int my_last_row=(my_rank+1) * local_m - 1;
	for(i=my_first_row; i<my_last_row; i++){
		y[i] = 0.0;
		for(j=0; j<n; j++) y[i] += A[i][j] * x[j];
		}
	return NULL;
	}
  
  
int main(int argc, char *argv[]){
	long thread;
	pthread_t * thead_handles;
	int i, j;
	for(i=0; i<n; i++) x[i] = 2; //vector init
	for(i=0; i<m; i++) for(j=0; j<n; j++) A[i][j] = 3; //matrix init
	
	thread_count = strtol(argv[i], NULL, 10);
	thread_handles = malloc(thread_count * sizeof(pthread_t));
	
	for(thread=0; thread<thread_count; thread++)
		pthread_create(&thread_handles[thread],NULL, Pth_mat_vect, (void*)thread);

	for(thread=0; thread<thread_count; thread++)
		pthread_join(thread_handles[thread], NULL);
free(thread_handles);
retrun 0;
}

