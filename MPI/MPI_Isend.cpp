#include <iostream>
#include <mpi.h>

using namespace std;
int main(int argc,char *argv[]){
int size,rank;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank==0){
		int buf=5;
		MPI_Request request;
		MPI_Isend(&buf,1,MPI_INT,1,123,MPI_COMM_WORLD,&request);
	}
	if(rank==1){
		int buf2,flag;
		MPI_Status status;
		MPI_Request request;
		MPI_Irecv(&buf2,1,MPI_INT,0,123,MPI_COMM_WORLD,&request);
		MPI_Test(&request,&flag,&status);
		if(flag==0)
			MPI_Wait(&request,&status);
		cout<<"data recieved is : "<<buf2<<endl;
	}
MPI_Finalize();
return 0;
}
