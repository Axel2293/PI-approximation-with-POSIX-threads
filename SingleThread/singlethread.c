/* 
	Practica 1: calculo de aproximacion de PI con un solo hilo
	Axel Escoto Garcia
	Sergio Villa Rodriguez
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        perror("[-] Too few Arguments\n\tUsage: piaproximation <Precision (num of rectangels)>");
        exit(EXIT_FAILURE);
    }
    long precision = atol(*(argv + 1));
    printf("[+] Precision set to %ld\n", precision);

    double pi = 0;
    double base_all = (double)1 / (double)precision; // Devide 1 to get all the bases of the rectangle
    double half = base_all / 2.0;

    struct timeval tval_before, tval_after, tval_result;
    gettimeofday(&tval_before, NULL); // Take time at start of algorithm
    // Start of calculations
    for (double i = 0; i <= 1.0; i += base_all)
    {
        double base_curr = i + base_all;
        double height = sqrt(1.0 - pow(i - half, 2)); // Calculate the height on the mid base point
        pi += base_all * height;
    }
    gettimeofday(&tval_after, NULL);
    timersub(&tval_after, &tval_before, &tval_result); // Get execution time

    printf("[+]\tFinished with time %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    printf("[+]\tPI: %.20F\n", pi * 4);

    return 0;
}
