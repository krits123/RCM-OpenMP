SHELL := /bin/bash

# define the C/C++ compiler to use,default here is clang
CC = gcc

# define compile-time flags
CFLAGS = -O3 -fopenmp -Wall


INCLUDES =	-I inc

.PRECIOUS: %.a

all:	src/main.c src/rcm_omp.c
	$(CC) $(CFLAGS) $(INCLUDES) -c src/rcm_omp.c -o  src/rcm_omp.o
	ar rcs lib/rcm_omp.a src/rcm_omp.o
	rm src/rcm_omp.o
	$(CC) $(CFLAGS) $(INCLUDES) -o main_openmp src/main.c lib/rcm_omp.a

lib:	src/rcm_omp.c
	$(CC) $(CFLAGS) $(INCLUDES) -c src/rcm_omp.c -o  src/rcm_omp.o
	ar rcs lib/rcm_omp.a src/rcm_omp.o
	rm src/rcm_omp.o


clean:
		$(RM) count main_openmp *.o *~ lib/*.a 
