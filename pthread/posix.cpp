#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <omp.h>
//#define SIZE 10
double A[SIZE][SIZE];
double B[SIZE][SIZE];
double C[SIZE][SIZE]={{0}};					// initialized by 0

void * func(void *id){						// the created threads run this portion of code
	int tid= * (int *)id;
	for(int i=0;i<SIZE;i++)
		for(int j=0;j<SIZE;j++)
			C[i][j]=C[i][j]+A[i][tid]*B[tid][j];	// I have converted 3-nested loop into 2-nested loop
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


	pthread_t trd[SIZE];				// declare an array of threads
	// parallel region starts here
	for(int id=0;id<SIZE;id++){
	pthread_create(&trd[id],NULL,&func,&id);	// creates thread with id
	pthread_join(trd[id],NULL);			// main thread waits for child threads to complete execution
	}
	// parallel region ends here
	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed  = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

	for (t = 0; t < SIZE; t++) {
		for (u = 0; u < SIZE; u++) {
			printf("%.0f ", C[t][u]);
		}
		printf("\n");
	}

	fprintf(stderr, "Time: %f s\n", elapsed);
}
