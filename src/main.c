#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>

#define NTHREADS 4
#define rectangels 100000000000

pthread_mutex_t *lock;
 	//Divides the calculation area for the threads
double part =1.0/(double)NTHREADS;
	// Calculates the bases for every rectangel
double base = 1.0/ (double)rectangels;
double  pi;

void * thread_func(void* arg){

	int *thread_num = (int*)arg;
	printf("[+]\tThread %d; Starting calculations\n",*thread_num);
	// Calculate ranges for the thread
	double START = (*thread_num) * part;
	double END = ((*thread_num) +1) * part;

	// double base_all=1.0/rectangels;
	double base_half=base/2.0;
	double area=0;

	for (double i = START; i <= END; i+=base)
	{
		double height = sqrt(1.0-pow(i-base_half, 2));
		area+=base*height;
	}
	
	pthread_mutex_lock(lock);
	pi+=area;
	pthread_mutex_unlock(lock);
	return NULL;
} 

int main(int argc, char*argv[]){
	//Divides the calculation area for the threads
	part =1.0/( double)NTHREADS;
	// Calculates the bases for every rectangel
	base = 1.0/ ( double)rectangels;
	//printf("PART: %.20F\nBASE: %.20F\n", part, base);

	pthread_t *tid= malloc(sizeof(pthread_t)*NTHREADS); //To store TID of threads
	int *t_num=malloc(sizeof(int)*NTHREADS); // Numbers of threads
	lock = malloc(sizeof(pthread_mutex_t)); // Mutex mem
	pthread_mutex_init(lock,NULL); 	//Create mutex

	struct timeval tval_before, tval_after, tval_result;
	gettimeofday(&tval_before, NULL);

	for (uint16_t i = 0; i < NTHREADS; i++)
	{
		t_num[i]=i;
		// Create thread
		pthread_create(&tid[i], NULL, thread_func, &t_num[i]);	
	}

	//Wait for threads to finish
	for (size_t i = 0; i < NTHREADS; i++)
	{
		//Wait for threads to finish
		pthread_join(tid[i], NULL);
	}
	gettimeofday(&tval_after, NULL);
	timersub(&tval_after, &tval_before, &tval_result);

	printf("[+]\tThreads finished with time %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
	printf("[+]\tPI result: %.16F\n", pi*(( double)4));
	
	
	return 0;
}
