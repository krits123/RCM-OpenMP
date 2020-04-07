# RCM-OpenMP
An implementation of the Reverse Cuthill McKee algorithm for Sparse matrix premutation using OpenMp

# How to Use

The project structure is :

|-- Makefile
|-- lib/
         -rcm_omp.a
|-- src/
        -main.c
        -rcm_omp.c
|-- inc/
        -rcm_omp.h

You can type make lib to compile the "rcm_omp.c" and create a library inside the lib folder or make to build the whole project and create an executable with the name "./main_openmp.exe".
Make clean can also be used.
The programm takes as input 4 command line arguments :
  1)Size of the "n" of the Sparse Matrix(The matrix is n rows by n collumns).
  2)The number of non-zero elements
  3)The name of the binary file that the matrix is stored in.
  4)The name of the output file, the premutation vector will be stored in that file.
 
 For my exepriments i used Sparse Matrixes from the UF Sparse Matrix Collection at : https://www.cise.ufl.edu/research/sparse/matrices/list_by_id.html
 
 I have provided some matrixes as bin files in the Sparse_Collection_Bin.zip file and a collection of matlab scripts that can take 
 a downloaded matrix from a collection as '.mat' file and convert it to a bin file that the programm can read.
 Information about the matrixes (size,number of non zeros...) are provided in the .xlsx allong with the command line input you need in order to run the programm for a given matrix.
 
 Finally to compare the resaulting premutations i used matlab and spy plot's and compared the resaults with matlabs version
 and to compare the execution time i used a c++ version of the rcm algorithm implemented in the boost library :
 https://www.boost.org/doc/libs/1_46_0/libs/graph/doc/cuthill_mckee_ordering.html
 An example for using this library can be found at : https://www.boost.org/doc/libs/1_46_0/libs/graph/example/cuthill_mckee_ordering.cpp
 I added to that example the file my reading function and used it. The code for the example + the read file function can be found at the existing_implementation Folder.
 
