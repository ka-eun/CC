# reduction operator    
-하나의 결과값을 위해 연속으로 같은 연산을 반복하는 연산    
-모든 연산 결과는 같은 변수(reduction variable)에 저장되어야 함   
-reduction 변수는 shared지만 parallel block에서 각 쓰레드별로 private변수가 생성되고 공유변수로 combine된다.    
-각 private변수는 0으로 초기화 됨      
```c
global_result = 0.0;    
#pragma omp parallel num_threads(thread_count) reduction(+: global_result)   
	global_result += Local_trap(a, b, n); 
  ```
   
# parallel for     
-for루프를 병렬화시킴 → 하나의 for loop의 iteration을 나누어서 하는 것   

```c
#pragma omp parallel for num_threads(thread_count) reduction (+: approx)      
	for(i=1; i<=n-1; i++) approx += f(a+i*h);   
  ```
→ 피보나치처럼 순서가 필요한 iteration(data dependency)   

## 파이값 구하기   
- sol1) loop dependency    
```c
#pragma omp parallel for num_threads(thread_count) reduction(+: sum)   
	for(k=0; k<n; k++){   
		sum += factor/(2*k+1);   
		factor =- factor;   
		}   
	pi_approx = 4.0 * sum;
```
   
   
- sol2)   
```c
#pragma omp parallel for num_threads(thread_count) reduction(+: sum) private(factor)   
	for(k=0; k<n; k++){   
		if(k%2==0) factor = 1.0;   
		else factor = -1.0;   
		sum += factor/(2*k+1);   
		}
```
   
   
   
# default clause    
-블록 밖에서 선언된 변수들의 scope를 컴파일러에서 필요로함   
```c
#pragma omp parallel for num_threads(thread_count) default(none) reduction(+: sum) private(k, factor) shared(n)
```
    
## Sorting   
- Serial한 odd-even transposition sort      
```c
for(phase=0; phase<n; phase++)   
	if(phase%2 ==0)   
		for(i=1; i<n; i+=2) if (a[i-1]>a[i]) Swap(&a[i-1], &a[i]);   
	else    
		for(i=1; i<n-1; i+=2) if (a[i]>a[i+1]) Swap(&a[i], &a[i+1]);
```    
    
- openmp sol1 : two parallel for directives    
```c
for(phase=0; phase<n; phase++)   
	if(phase%2==0)   
		#pragma omp parallel for num_threads(thread_count) default(none) shared(a, n) private(i, tmp)   
	for(i=1; i<n; i+=2) if (a[i-1]>a[i]) Swap(&a[i-1], &a[i]);    
else   
		#pragma omp parallel for num_threads(thread_count) default(none) shared(a, n) private(i, tmp)   
	for(i=1; i<n-1; i+=2) if (a[i]>a[i+1]) Swap(&a[i], &a[i+1]);
  ```
  
- openmp sol2 : two for directives 
```c
#pragma omp parallel num_threads(thread_count) default(none) shared(a, n) private(i, tmp, phase)   
for(phase=0; phase<n; phase++)   
	if(phase%2==0)   
		#pragma omp for   
	for(i=1; i<n; i+=2) if (a[i-1]>a[i]) Swap(&a[i-1], &a[i]);   
	else   
		#pragma omp for   
		for(i=1; i<n-1; i+=2) if (a[i]>a[i+1]) Swap(&a[i], &a[i+1]); 
 ```
    

# Scheduling loop    
for루프를 돌면서 iteration time이 다르면 default보다 cyclic으로 하는게 더 효율적임
   
- default schedule      
```c 
sum=0.0;   
#pragma omp parallel for num_threads(thread_count) reduction(+: sum)      
for(i=0; i<=n; i++) sum+=f(i);    
```
   
- cyclic schedule      
```c
sum=0.0;   
#pragma omp parallel for num_threads(thread_count) reduction(+: sum) schedule(static, i)   
for(i=0; i<=n; i++) sum+=f(i);   
```
   
## schedule clause : schedule(type, chunksize)   
type   
-static: iteration이 루프 실행 전에 할당됨   
-dynamic or guided : 루프 실행중에 할당됨   
   
## dynamic schedule 
-각 쓰레드에서 chunk만큼 한번에 실행. 한 chunk끝나면 runtime sys한테 next 받아옴   
-iteration끝날때까지 반복됨   
-chunk생략시 1로 초기화됨   
   
## guided schedule 
-각 쓰레드에서 chunk만큼 한번에 실행. 한 chunk끝나면 runtime sys한테 next 받아옴   
-chunk size를 크게 해놓고 줄여가면서 쓰레드에게 할당→ 점점 차이 줄어듦   
-chunk생략시 1로 초기화됨   



