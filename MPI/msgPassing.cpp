#include <iostream>
#include <mpi.h>

using namespace std;
int main(int argc,char *argv[]){
	int size,rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank==0){
		int buffer1[10];
		for(int i=0;i<10;i++)
		buffer1[i]=i+1;
		MPI_Send(buffer1, 10, MPI_INT, 1,345, MPI_COMM_WORLD);
	}
	else if(rank==1){
		int buffer2[10];
		MPI_Status status;
		MPI_Recv(buffer2, 10, MPI_INT, 0,345, MPI_COMM_WORLD,&status);
		for(int i=0;i<10;i++)
		cout<<buffer2[i]<<" ";
		cout<<endl;
	}
	else{
		cout<<"Processor : "<<rank<<endl;
	}

	MPI_Finalize();

return 0;
}
