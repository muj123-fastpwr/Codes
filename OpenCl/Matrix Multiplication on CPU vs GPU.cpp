#include <iostream>
#include <stdio.h>
#include <CL/cl.h>
#include <assert.h>
#include <string.h>

using namespace std;
//#define SIZE 10	// delete this line when testing is complete

long PROBSIZE=SIZE;
float *A;
float *B;
float *C;

cl_ulong matrixMultiplicationCPU(float *, float *, float *);
cl_ulong matrixMultiplicationGPU(float *, float *, float *);
cl_ulong profileThis(cl_event, cl_command_queue *);

int main()
{
	int t, u;

	/* Declare Matrices */
	A = new float[SIZE*SIZE];
	B = new float[SIZE*SIZE];
	C = new float[SIZE*SIZE];

	/* Input Data into Matrices */
	for (t = 0; t < SIZE; t++) {
		for (u = 0; u < SIZE; u++) {
			A[t*SIZE+u] = B[t*SIZE+u] = 1;
		}
	}

	
	float gpu_time = matrixMultiplicationGPU(A, B, C);
	float cpu_time = matrixMultiplicationCPU(A, B, C);

	for (t = 0; t < SIZE; t++) {
		for (u = 0; u < SIZE; u++) {
			cout<<C[t*SIZE+u]<<" ";
		}
		cout<<endl;
	}

//	cout<<"Time: "<<gpu_time*1e-9<<"\t"<<cpu_time*1e-9<<endl;
	fprintf(stderr, "Time: %f s %f s\n", gpu_time*1e-9, cpu_time*1e-9);	// Do not modify this line
}

cl_ulong profileThis(cl_event a, cl_command_queue *c)
{
	clFinish(*c);
	cl_ulong start = 0, end = 0;
	clGetEventProfilingInfo(a, CL_PROFILING_COMMAND_END, 
							sizeof(cl_ulong), &end, NULL);
	clGetEventProfilingInfo(a, CL_PROFILING_COMMAND_START, 
							sizeof(cl_ulong), &start, NULL);
	return (end - start);
}

cl_ulong matrixMultiplicationCPU(float *A, float *B, float *C)
{
	cl_event myEvent;
	cl_ulong elapsed = 0;
	
	cl_int ret;
	cl_uint numPlatforms;
	cl_platform_id *platform;

	ret = clGetPlatformIDs(0, NULL, &numPlatforms);
	assert (ret == CL_SUCCESS);
	platform = new cl_platform_id[numPlatforms];
	
	ret = clGetPlatformIDs(numPlatforms, platform, NULL);
	
	assert (ret == CL_SUCCESS);

	int mytarget=1;

	size_t size;
	ret = clGetPlatformInfo(platform[mytarget], CL_PLATFORM_NAME, 0, NULL, &size);
	assert (ret == CL_SUCCESS);
	if(ret!=CL_SUCCESS){cout<<"getting size of platform name failed.."<<ret<<endl; return 0;}
	char * name = new char[sizeof(char)*size];

	ret = clGetPlatformInfo(platform[mytarget], CL_PLATFORM_NAME, size, name,NULL);
	assert (ret == CL_SUCCESS);
	if(ret!=CL_SUCCESS){cout<<"getting platform info failed.."<<ret<<endl; return 0;}
	assert (ret == CL_SUCCESS);	
	ret = clGetPlatformInfo(platform[mytarget], CL_PLATFORM_VENDOR, 0, NULL, &size);
	char *vname = new char[sizeof(char)*size];
	ret = clGetPlatformInfo(platform[mytarget], CL_PLATFORM_VENDOR, size, vname, NULL);
	assert (ret == CL_SUCCESS);	
	cout<<"platform No : "<<mytarget<<endl;
	cout<<"platform name : "<<name<<endl;
	cout<<"platform vendor : "<<vname<<endl;

	cl_device_id device;
	cl_uint numDevices;
	ret = clGetDeviceIDs(platform[mytarget], CL_DEVICE_TYPE_CPU, 1, &device, &numDevices);
	assert (ret == CL_SUCCESS);
	if(ret!=CL_SUCCESS){
		cout<<"getting device id failed : "<<ret<<endl;
	}
	char buffer[2048];
	ret = clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof(char)*2048, buffer, NULL);
	assert (ret == CL_SUCCESS);	

	cout<<"device id : "<<device<<endl;
	cout<<"device vendor : "<< buffer<<endl;
	cout<<"num of devices : "<<numDevices<<endl;

	cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &ret);
	assert (ret == CL_SUCCESS);
	if(ret !=CL_SUCCESS){
		cout<<"context creation failed.. "<<context<<endl;
	}
	cl_command_queue queue = clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, &ret);
	assert (ret == CL_SUCCESS);
	if(ret !=CL_SUCCESS){
		cout<<"queue creation failed... "<<queue<<endl;
	}
	

	const char * source_code =  "__kernel void matrixMul(__global float *A,\
								 __global float *B,\
								 __global float *C){\
					int i = get_global_id(0);\
					int j = get_global_id(1), k;\
					int gsize = get_global_size(0);\
						for(k=0;k<gsize;k++)\
						C[i*gsize + j] =  C[i*gsize + j] +  A[i*gsize + k] * B[k*gsize +j];\
					}";
	cl_program program = clCreateProgramWithSource(context, 1, &source_code, NULL, &ret);
	assert (ret == CL_SUCCESS);

	ret = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	char bb[65536];
	clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(char)*65536, bb, NULL);
	printf("Build Log: %s\n", bb);
	assert(ret == CL_SUCCESS);

	cl_kernel kernel = clCreateKernel(program, "matrixMul", &ret);
	
	float dataSize=SIZE*SIZE;

	
	cl_mem dataA = clCreateBuffer(context, CL_MEM_READ_ONLY,sizeof(float)*dataSize, NULL, &ret);
	cl_mem dataB = clCreateBuffer(context, CL_MEM_READ_ONLY,sizeof(float)*dataSize, NULL, &ret);
	cl_mem dataC = clCreateBuffer(context, CL_MEM_READ_WRITE,sizeof(float)*dataSize, NULL, &ret);
	assert (ret == CL_SUCCESS);	
	
	ret = clEnqueueWriteBuffer(queue, dataA, CL_TRUE, 0, sizeof(float)*dataSize, A, 0, NULL, &myEvent);
	elapsed += profileThis(myEvent, & queue);
	ret = clEnqueueWriteBuffer(queue, dataB, CL_TRUE, 0, sizeof(float)*dataSize, B, 0, NULL, &myEvent);
	elapsed += profileThis(myEvent, & queue);
	ret = clEnqueueWriteBuffer(queue, dataC, CL_TRUE, 0, sizeof(float)*dataSize, C, 0, NULL, &myEvent);
	elapsed += profileThis(myEvent, & queue);
	
	ret = clSetKernelArg(kernel, 0, sizeof(dataA), (void *)&dataA);
	assert(ret == CL_SUCCESS);
	ret = clSetKernelArg(kernel, 1, sizeof(dataB), (void *)&dataB);
	assert(ret == CL_SUCCESS);
	ret = clSetKernelArg(kernel, 2, sizeof(dataC), (void *)&dataC);
	assert(ret == CL_SUCCESS);

	size_t globalsize[2], localsize[2];
	globalsize[0] = SIZE;
	globalsize[1] = SIZE;
	localsize[0] = 1;
	localsize[1] = 1;
	ret = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, globalsize, localsize, 0, NULL, &myEvent);
	assert (ret == CL_SUCCESS);
	elapsed += profileThis(myEvent, & queue);
	cout << ret << endl;
	assert(ret == CL_SUCCESS);
	
	ret = clEnqueueReadBuffer(queue, dataC , CL_TRUE, 0, sizeof(float)*dataSize, C, 0, NULL, &myEvent);
	elapsed += profileThis(myEvent, & queue);
	cout << ret << endl;
	assert(ret == CL_SUCCESS);
	
	return elapsed;
}

cl_ulong matrixMultiplicationGPU(float *A, float *B, float *C)
{
	cl_event myEvent;
	cl_ulong elapsed = 0;

	cl_int errNum;
	cl_uint numPlatforms;
	cl_platform_id *platform;

	errNum = clGetPlatformIDs(0, NULL, &numPlatforms);
	if(errNum!=CL_SUCCESS){
		cout<<"getting platform failed.."<< errNum << endl; return 0;
	}
	assert (errNum == CL_SUCCESS);
	platform = new cl_platform_id[numPlatforms];
	
	errNum=clGetPlatformIDs(numPlatforms, platform, NULL);
	if(errNum!=CL_SUCCESS){cout<<"getting platform IDs failed.."<<endl; return 0;}
	assert (errNum == CL_SUCCESS);

	int i;
	int mytarget;
	char buffer[2048];
	for (i = 0; i < numPlatforms; i++) 
	{
		errNum = clGetPlatformInfo(platform[i], CL_PLATFORM_NAME, sizeof(char)*2048, &buffer, NULL);
		if (strcmp(buffer, "NVIDIA CUDA") == 0)  
			mytarget = i;
	}


	size_t size;
	errNum = clGetPlatformInfo(platform[mytarget], CL_PLATFORM_NAME, 0, NULL, &size);
	if(errNum!=CL_SUCCESS){cout<<"getting size of platform name failed.."<<errNum<<endl; return 0;}
	char * name = new char[sizeof(char)*size];

	errNum = clGetPlatformInfo(platform[mytarget], CL_PLATFORM_NAME, size, name,NULL);
	if(errNum!=CL_SUCCESS){cout<<"getting platform info failed.."<<errNum<<endl; return 0;}
	
	errNum = clGetPlatformInfo(platform[mytarget], CL_PLATFORM_VENDOR, 0, NULL, &size);
	char *vname = new char[sizeof(char)*size];
	errNum = clGetPlatformInfo(platform[mytarget], CL_PLATFORM_VENDOR, size, vname, NULL);
	
	cout<<"platform No : "<<mytarget<<endl;
	cout<<"platform name : "<<name<<endl;
	cout<<"platform vendor : "<<vname<<endl;

	cl_device_id device;
	cl_uint numDevices;
	errNum = clGetDeviceIDs(platform[mytarget], CL_DEVICE_TYPE_GPU, 1, &device, &numDevices);
	if(errNum!=CL_SUCCESS){
		cout<<"getting device id failed : "<<errNum<<endl;
	}

	errNum = clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof(char)*2048, buffer, NULL);
	

	cout<<"device id : "<<device<<endl;
	cout<<"device vendor : "<< buffer<<endl;
	cout<<"num of devices : "<<numDevices<<endl;

	int ret;
	cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &ret);
	if(ret !=CL_SUCCESS){
		cout<<"context creation failed.. "<<context<<endl;
	}
	cl_command_queue queue = clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, &ret);
	if(ret !=CL_SUCCESS){
		cout<<"queue creation failed... "<<queue<<endl;
	}
	

	const char * source_code = "__kernel void matrixMul(__global float *A,\
								 __global float *B,\
								 __global float *C){\
					int i = get_global_id(0);\
					int j = get_global_id(1), k;\
					int gsize = get_global_size(0);\
					for(k=0;k<gsize;k++)\
						C[i*gsize + j] =  C[i*gsize + j] +  A[i*gsize + k] * B[k*gsize +j];\
					}";
	cl_program program = clCreateProgramWithSource(context, 1, &source_code, NULL, &ret);
	assert (ret == CL_SUCCESS);

	ret = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	char bb[65536];
	clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(char)*65536, bb, NULL);
	printf("Build Log: %s\n", bb);
	assert(ret == CL_SUCCESS);

	cl_kernel kernel = clCreateKernel(program, "matrixMul", &ret);
	
	float dataSize=SIZE*SIZE;
	
	
	cl_mem dataA = clCreateBuffer(context, CL_MEM_READ_ONLY,sizeof(float)*dataSize, NULL, &ret);
	cl_mem dataB = clCreateBuffer(context, CL_MEM_READ_ONLY,sizeof(float)*dataSize, NULL, &ret);
	cl_mem dataC = clCreateBuffer(context, CL_MEM_READ_WRITE,sizeof(float)*dataSize, NULL, &ret);
	
	
	ret = clEnqueueWriteBuffer(queue, dataA, CL_TRUE, 0, sizeof(float)*dataSize, A, 0, NULL, &myEvent);
	elapsed += profileThis(myEvent, & queue);
	ret = clEnqueueWriteBuffer(queue, dataB, CL_TRUE, 0, sizeof(float)*dataSize, B, 0, NULL, &myEvent);
	elapsed += profileThis(myEvent, & queue);
	ret = clEnqueueWriteBuffer(queue, dataC, CL_TRUE, 0, sizeof(float)*dataSize, C, 0, NULL, &myEvent);
	elapsed += profileThis(myEvent, & queue);
	
	ret = clSetKernelArg(kernel, 0, sizeof(dataA), (void *)&dataA);
	assert(ret == CL_SUCCESS);
	ret = clSetKernelArg(kernel, 1, sizeof(dataB), (void *)&dataB);
	assert(ret == CL_SUCCESS);
	ret = clSetKernelArg(kernel, 2, sizeof(dataC), (void *)&dataC);
	assert(ret == CL_SUCCESS);

	size_t globalsize[2], localsize[2];
	globalsize[0] = SIZE;
	globalsize[1] = SIZE;
	localsize[0] = 1;
	localsize[1] = 1;
	ret = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, globalsize, localsize, 0, NULL, &myEvent);
	elapsed += profileThis(myEvent, & queue);
	cout << ret << endl;
	assert(ret == CL_SUCCESS);
	
	ret = clEnqueueReadBuffer(queue, dataC , CL_TRUE, 0, sizeof(float)*dataSize, C, 0, NULL, &myEvent);
	elapsed += profileThis(myEvent, & queue);
	cout << ret << endl;
	assert(ret == CL_SUCCESS);

	return elapsed;
}
