 ThreadProgram 구조
1. thread_handles = malloc()
2. pthread_create()
3. pthread_join()
4. free(thread_handles()) 
   
Compile :   
gcc -g -Wall -o Hello Hello.c -lpthread   

Excecute :    
./Hello <threadnum>
