#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>

#define NTHREADS 4

pthread_mutex_t *lock;
double part;
double base;
double base_half;
double pi;

void *thread_func(void *arg)
{

	int *thread_num = (int *)arg;
	printf("[+] Thread %d; Starting calculations\n", *thread_num);
	// Calculate ranges for the thread
	double START = (*thread_num) * part;
	double END = ((*thread_num) + 1) * part;

	double area = 0;

	for (double i = START; i <= END; i += base)
	{
		double height = sqrt(1.0 - pow(i - base_half, 2));
		area += base * height;
	}

	pthread_mutex_lock(lock);
	pi += area;
	pthread_mutex_unlock(lock);
	return NULL;
}

int main(int argc, char **argv)
{

	if (argc != 2)
	{
		perror("[-] Too few Arguments\n\tUsage: piaproximation <Precision (num of rectangels)>");
		exit(EXIT_FAILURE);
	}
	long precision = atol(*(argv + 1));
	printf("[+] Precision set to %ld\n", precision);

	// Divides the calculation area for the threads
	part = 1.0 / (double)NTHREADS;
	// Calculates the bases for every rectangle
	base = 1.0 / (double)precision;
	// Calculate the midpoint of every base
	base_half = base / 2.0;

	pthread_t *tid = malloc(sizeof(pthread_t) * NTHREADS); // To store TID of threads
	int *t_num = malloc(sizeof(int) * NTHREADS);		   // Numbers of threads
	lock = malloc(sizeof(pthread_mutex_t));				   // Mutex mem
	pthread_mutex_init(lock, NULL);						   // Create mutex

	struct timeval tval_before, tval_after, tval_result;
	gettimeofday(&tval_before, NULL);

	for (uint16_t i = 0; i < NTHREADS; i++)
	{
		t_num[i] = i;
		// Create thread
		if (pthread_create(&tid[i], NULL, thread_func, &t_num[i]) != 0)
		{
			perror("[-] Could not create Thread");
			exit(EXIT_FAILURE);
		}
	}

	// Wait for threads to finish
	for (size_t i = 0; i < NTHREADS; i++)
	{
		pthread_join(tid[i], NULL);
	}
	gettimeofday(&tval_after, NULL);
	timersub(&tval_after, &tval_before, &tval_result);

	printf("[+]\tThreads finished with time %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
	printf("[+]\tPI result: %.20F\n", pi * ((double)4));

	return 0;
}
