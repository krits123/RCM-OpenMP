#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include "rcm.h"








int main(int argc,char* argv[]){


  if(argc!=5){

    printf("You need to give 4 arguments :\n1.Number o vertexes\n2.Number of non zero values\n3.Input file name\n4.Output file name");
    exit(1);
  }
  int n = atoi(argv[1]);
  int nnz = atoi(argv[2]);
  printf("Hello World\n");




 // Timing
  struct timeval startwtime, endwtime;
  double seq_time;

//

  //int n = 28924;

  //int n = 8032;

	//int nnz = 355460;
	//int nnz = 2043492;

  sparseMatrix *A;
	A = (sparseMatrix*)malloc(sizeof(sparseMatrix));
  if(A == NULL)
  {
      printf("Memory coudldn't be allocated exiting...\n");
      exit(1);
  }

	initSpMat(A,nnz);


  // Preumation vector returned by rcm
  int *prem =(int*) malloc(n*sizeof(int));

  if(prem == NULL)
  {
      printf("Memory coudldn't be allocated exiting...\n");
      exit(1);
  }


	//readSparseMatrix("big2.bin",A,nnz);
	//readSparseMatrix("large.bin",A,nnz);
  readSparseMatrix(argv[3],A,nnz);
  //printf("Finished Reading");

  int *D = (int*)malloc(n*sizeof(int));
  // Stores the deggre if each vertex
  if(D == NULL)
  {
      printf("Memory coudldn't be allocated exiting...\n");
      exit(1);
  }
	int *firsts = (int*)malloc(n*sizeof(int));
  // firsts[i] Stores the index of the first occurance of the ith node in the
  // Sparse Matrix col vector, which is sorted 
	if(firsts == NULL)
  {
      printf("Memory coudldn't be allocated exiting...\n");
      exit(1);
  }

//  printf("The matrix size NxN is divided into  : %d chunks \n",NUMTHREADS );


  printf("\nNUMTHREADS : %d\t | SQTH : %d\t | MAXDEPTH : %d \n",NUMTHREADS,SEQTH,MAXDEPTH);
  printf("Current matrix is : %s\n",argv[3] );
	// Run and time the rcm algorithm
  gettimeofday( &startwtime, NULL );
  // Calculate the degree for each node
	getMatDegree(A,D,firsts,nnz,n);
	rcmOmp(A,D,firsts,prem,n,nnz);
  gettimeofday( &endwtime, NULL );
  seq_time = (double)( ( endwtime.tv_usec - startwtime.tv_usec ) / 1.0e6 + endwtime.tv_sec - startwtime.tv_sec );
  printf("Open MP method time is %f secconds.\n",seq_time );


	freeSpMat(A);


	// Print Resaults
//  printArray(prem,n);


  // write output to file


  FILE *fp;

  	//fp = fopen("res_large.bin", "wb");
    //fp = fopen("resBucky.bin", "wb");
    fp = fopen(argv[4], "wb");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    fwrite(prem, sizeof(int), n, fp);

    fclose(fp);

  // Free memory
  // The rest of the memory is cleaned in rcmOmp
  free(prem);
  return 1;


}
