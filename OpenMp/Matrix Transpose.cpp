#include <iostream>
#include <omp.h>
using namespace std;
const int SIZE=10;

void transpose(int A[SIZE][SIZE], int tid){
	int temp;
	for(int i=tid;i<SIZE;i++){
		temp=A[tid][i];
		A[tid][i]=A[i][tid];
		A[i][tid]=temp;
	}
}
int main(){

	int A[SIZE][SIZE];
	for(int i=0;i<SIZE;i++)
		for(int j=0;j<SIZE;j++)
			A[i][j]=(i+1)*SIZE+j;

	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++)
			cout<<A[i][j]<<" ";
		cout<<endl;
	}

	int tid;
	#pragma omp parallel num_threads(SIZE) private(tid)
	{
		tid=omp_get_thread_num();
		transpose(A,tid);
	//	transpose(A,tid);
	}
cout<<endl<<endl;
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++)
			cout<<A[i][j]<<" ";
		cout<<endl;
	}
	return 0;
}
