#ifndef RCM_H
#define RCM_H

// Define Basic Parameters about thread numbers

#define NUMTHREADS 4 // Indicates number of threads that can run something in parralell
#define SEQTH 6000 // Threshold below of wich the sortings is sequential
#define MAXDEPTH 2 // Max recursion depth of parallel sorting


//------------------------------------------------------------------------------
// Define structs
// This struct represnets a sparse Matrix
typedef struct sparseMatrix{
  int* row;// vector of size equal to the num of non-zero elems of the array
  int* col;//vector of size equal to the num of non-zero elems of the array
  // Each pair of {row[i],col[i]} represents a non zero entry of the sparse matrix
  // The entries in the col vetor are always sorted

}sparseMatrix;


// Implementation of a Queue
typedef struct rcmQueue{

  int* elems; // List of vertex labels
  int start_; // Pointer to the starrt of Queue
  int end_; // Pointer to the end of Queue
  int size; // Current number of elements
  int N; // Max Queue Size

}rcmQueue;

// This structure stores the temporarilly the resaults
typedef struct rcmRes{

  int *elems; // List of vertex Labels
  int size; // Current number of elements
  int N; // Max list size

}rcmRes;

// This structure is used when doing a Bread First search and stores temporarilly the new adjacent nodes found
typedef struct vertexNeibs{

  int *neibs; // Array that contains label of adjacent vertexes
  int cnt; // NUmber of adjacent vertexes found
  int *D; // Array that contains deggres of each vertex
}vertexNeibs;


//------------------------------------------------------------------------------
// Declare functions

//Functions that impliment the sparse Matrix

void readSparseMatrix(const char* file_name,sparseMatrix *A, int n);
void initSpMat(sparseMatrix *A,int nnz);
void freeSpMat(sparseMatrix *A);

// Functions that impliment the vertexNeibs struct
void initVN(vertexNeibs* vn,int n,int *D);
void freeVn(vertexNeibs *vn);

// Basic resaults matrix functionallity

int isRFull(rcmRes *R);
void initR(rcmRes *R,int *prem,int n);
void add2R(rcmRes *R,int key);


// Baisc Queue Functionallity

void initQ(rcmQueue *q,int N);
void add2Q(rcmQueue* q,int key);
int popFromQ(rcmQueue *q);
int isEmpty(rcmQueue *q);
int isFull(rcmQueue *q);
void freeQ(rcmQueue *q);

// Basic Functions

void getNewNeibs(sparseMatrix* A,int vertex,vertexNeibs *verNeibs,int *firsts,int *P,int n,int *totalNeibsFound);
void sortVn(vertexNeibs *vn);
void addVn2Q(vertexNeibs *vn,rcmQueue *q);
int getMinDegree(int *P,int *D,int n);
void reverseR(rcmRes *R);
void rcmOmp(sparseMatrix *A,int *D,int *firsts,int *prem,int n,int nnz);
void fillRPar(rcmRes *R,rcmQueue *q);
void getMatDegree(sparseMatrix *A,int *D,int *firsts,int nnz,int n);
int findFirstOc(int *arr, int low, int high, int x, int n);
int findLastOc(int *arr, int low, int high, int x, int n);

// Sorting Functions

void swap(int* a, int* b);
int partition (int *arr,int *D, int low, int high);
void quickSort(int *arr,int *D,int low, int high);
void quickSort_parallel_internal(int* arr,int* D,int low, int high,int depth );
void quickSortPar(int* arr,int *D ,int last);

// Helping functions

void printQueue(rcmQueue *q);
void testQueue(rcmQueue *q);
void printArray(int *arr,int size);




#endif
