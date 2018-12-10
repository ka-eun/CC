compile :     
gcc -g -Wall -fopenmp -o hello hello.c    
   
execute :   
./hello <number of threads>   

원래 쓰레드 : master + 새로운 쓰레드 : slaves --> team   
team은 block 실행시 implicit barrier 수행   
