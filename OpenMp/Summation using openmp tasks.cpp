#include <iostream>
#include <omp.h>
using namespace std;

int summation(int *arr,int n){
if(n==0)
return 0;
if(n==1)
return *arr;
else
return summation(arr,(n/2))+summation(arr+(n/2),n-(n/2));
}

int main()
{
int sum=0,sum1=0,sum2=0,size=100;
int arr[size];
for(int i=0;i<size;i++)
arr[i]=i+1;

#pragma omp parallel
#pragma omp single
{
	#pragma omp task shared(sum1)
	sum1=summation(arr,size/2);
	#pragma omp task shared(sum2)
	sum2=summation(arr+size/2,size/2);

	#pragma omp taskwait
	sum=sum1+sum2;
}
cout<<sum<<endl;

return 0;
}

