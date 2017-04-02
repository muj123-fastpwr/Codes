#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <omp.h>
//#define SIZE 10
double A[SIZE][SIZE];
double B[SIZE][SIZE];
double C[SIZE][SIZE]={{0}};

void * func(void *a){
	int tid= * (int *)a;
	for(int i=0;i<SIZE;i++)
		for(int j=0;j<SIZE;j++)
			for(int k=0;k<SIZE;k++)
			C[i][j]=C[i][j]+A[i][k]*B[k][j];		
	pthread_exit(NULL);
}

int main()
{
	int t, u;
	
	for (t = 0; t < SIZE; t++) {
		for (u = 0; u < SIZE; u++) {
			A[t][u] = B[u][t] = 1;
		}
	}

	struct timespec start, finish;
	double elapsed;

	clock_gettime(CLOCK_MONOTONIC, &start);

	
	pthread_t trd[SIZE];
	for(int i=0;i<SIZE;i++){
	pthread_create(&trd[i],NULL,&func,&i);
	pthread_join(trd[i],NULL);
	}

	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed  = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0; 
/*
	for (t = 0; t < SIZE; t++) {
		for (u = 0; u < SIZE; u++) {
			printf("%.0f ", C[t][u]);
		}
		printf("\n");
	}
*/
	fprintf(stderr, "Time: %f s\n", elapsed);	
}

