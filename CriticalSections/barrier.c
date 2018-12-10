/*
Barrier implemented by pthread


-쓰레드들이 같은 지점에서 있다는 것을 확인하기 위한 동기화작업.
-모든 쓰레드들이 도착하기 전까지 그 어느 애도 cross the barrier할 수 없음.
-critical section세가지 방법 모두에서 구현가능

point in program we want to reach;
barrier;
if (myrank==0) printf(“모든 쓰레드들이 여기 도착”);

-busywaiting&mutex로 구현하는 방법:
counter=0;
lock;
counter++;
unlock;
while(counter<thread_count);

-semaphore로 구현하는방법:
counter=0;
sem_wait(count)
if(counter == thread_count-1) counter0으로 하고 sem_post(count), sem_post(barrier);
else counter++하고 sem_pose(count), sem_wait(barrier);

또는
pthread_barrier_t mybarrier;
pthead_barrier_wait(&mybarrier);


*/
