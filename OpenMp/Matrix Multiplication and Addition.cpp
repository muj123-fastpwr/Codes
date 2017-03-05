#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <omp.h>
#define SIZE 5
double A[SIZE][SIZE];
double B[SIZE][SIZE];
double C[SIZE][SIZE]={{0}};
double D[SIZE][SIZE]={{0}};

void * func(void *a){
	int tid= * (int *)a;

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
#pragma omp parallel num_threads(2)
{
#pragma omp sections
{
	#pragma omp section
	for(int i=0;i<SIZE;i++)
			for(int j=0;j<SIZE;j++)
				for(int k=0;k<SIZE;k++)
				C[i][j]=C[i][j]+A[i][k]*B[k][j];
	#pragma omp section
	for(int i=0;i<SIZE;i++)
		for(int j=0;j<SIZE;j++)
			D[i][j]=A[i][j]+B[i][j];
	}

}

	printf("Multiplication Result \n");
	for (t = 0; t < SIZE; t++) {
		for (u = 0; u < SIZE; u++) {
			printf("%.0f ", C[t][u]);
		}
		printf("\n");
	}
	printf("\nAddition Result \n");
	for (t = 0; t < SIZE; t++) {
		for (u = 0; u < SIZE; u++) {
			printf("%.0f ", D[t][u]);
		}
		printf("\n");
	}

return 0;
}
