/* * http://people.math.sc.edu/Burkardt/cpp_src/metis_test/metis_test.cpp

- Purpose: METIS_TEST tests the METIS library.
- Licensing: This code is distributed under the GNU LGPL license. 
- Modified: 27 February 2017
- Author: John Burkardt
  
Load Module
  module load gcc
  module load metis
Build with
  gcc example_2_METIS.c  -lmetis -o out
  gcc example_2_METIS.c -L/usr/lib/x86_64-linux-gnu  -o out

1. Henry metis own installation
// only used for internal headers or for explicitly added directories (in gcc with the -I option).
//# include <metis.h> 
//directly include the header file in your code
# include "/usr/projects/climate/hrmoncada/repos/Sources/metis-5.1.0/include/metis.h" 

module load gcc
$ gcc -c example_2_METIS.c -o driver.o
$ gcc -o out driver.o -L. /usr/projects/climate/hrmoncada/repos/Sources/parmetis-4.0.3/metis/build/Linux-x86_64/libmetis/libmetis.a -lm

2. Grizzly-climate metis installation
mdlgrgnu
module load metis
# include "/usr/projects/climate/SHARED_CLIMATE/software/grizzly/metis/5.1.0/include/metis.h"
$ gcc -c example_2_METIS.c -o driver.o
$ gcc -o out driver.o -L. /usr/projects/climate/SHARED_CLIMATE/software/grizzly/metis/5.1.0/lib/libmetis.a -lm  

3. Oni
$ gcc -c example_2_METIS.c -o driver.o
$ gcc -o out driver.o -L. /home/hrmoncada/Desktop/MPAS_Ocean/Download/metis-5.1.0/build/Linux-x86_64/libmetis/libmetis.a -lm
$./out              
*/

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

// Only used for internal headers or for explicitly added directories (in gcc with the -I option).
//# include<metis.h>

// Directly include the header file in your code

// Henry own install
//# include "/usr/projects/climate/hrmoncada/repos/Sources/metis-5.1.0/include/metis.h" 
//# include "/usr/projects/climate/hrmoncada/repos/Sources/parmetis-4.0.3/metis0/include/metis.h" 

//Grizzly-climate
//# include "/usr/projects/climate/SHARED_CLIMATE/software/grizzly/metis/5.1.0/include/metis.h"

//Oni
# include "/home/hrmoncada/Desktop/MPAS_Ocean/Download/metis-5.1.0/include/metis.h" 
# include <string.h>

int built_arrays();
int* GetArrays(); 

int main ( );
void partgraphrecursive_test ( );
void timestamp ( );

int main ( ) {
  
  timestamp ( );
  
  printf ( "\n" );
  printf ( "METIS_TEST\n" );
  printf ( "  C version\n" );
  printf ( "  Test the METIS library for graph partitioning.\n" );

  partgraphrecursive_test ( );

  /*Terminate.*/
  printf ( "\n" );
  printf ( "METIS_TEST\n" );
  printf ( "  Normal end of execution.\n" );
  printf ( "\n" );
  
  timestamp ( );

  return 0;
}

/******************************************************************************
  Purpose: PARTGRAPHRECURSIVE_TEST tests PARTGRAPHRECURSIVE.

  Discussion: The graph has the following form:

      0 --- 1 --- 2
      |     |     |
      3 --- 4 --- 5
      
Vertex : Edges   Pointers:0
      0: 1 3        2  
      1: 0 4 2      5
      2: 1 5        7
      3: 0 4        9
      4: 3 1 5      12
      5: 4 2        14      
      
******************************************************************************/
void partgraphrecursive_test ( ) {

/*Extract from the 2003 C++ Standard: Each name that contains a double underscore (_ _) or begins with an underscore
followed by an lowercase/uppercase letter is reserved to the implementation for any use.

__int8, __int16, __int32, __int64

Microsoft C/C++ features support for sized integer types. You can declare 8-, 16-, 32-, or 64-bit integer variables
by using the __intn type specifier, where n is 8, 16, 32, or 64. The following example declares one variable for each
of these types of sized integers: 

C++

__int8 nSmall;      // Declares 8-bit integer
__int16 nMedium;    // Declares 16-bit integer
__int32 nLarge;     // Declares 32-bit integer
__int64 nHuge;      // Declares 64-bit integer

To simplify, __int32 is an int coded on 32 bits and __int64 on 64. You eliminate the size abstraction of the standard int type,
with this you're certain that the variable will allocate 4 bytes precisely

On Metis

 typedef __int32 int32_t;
 typedef __int64 int64_t; 

 typedef int32_t idx_t;  
 typedef int64_t idx_t; 
 
https://www.viva64.com/en/k/0046/ 
a) For the __int64 type, regardless of the compiler (C++Builder, MSVC, or GCC):

printf("%lld", i);

b) For the types size_t and ptrdiff_t:
                       Data type
Compiler      |      site_t      |  ptr diff_t       |
BCC or MSVC   | printf("%Iu", i) | printf("%Id", i); |
GCC           | printf("%zu", i) | printf("%zd", i); |
*/ 

/* Arrays */      
  int adjncy_[] = {};   // Declare and empty 1D array: Adjacent vertices in consecutive index order {1,3,0,4,2,1,5,0,4,3,1,5,4,2}  
  int xadj_[] = {};     // Declare and empty 1D array: Pointers to initial entries in adjacency array {0, 2, 5, 7, 9, 12, 14} 
  int array[] = {}; 
/*****************************************************************************************/    
  int *p = GetArrays(3, array, xadj_);

  for (int j = 0;j < 3;j++)  {  
      printf("%d ",*(p+j));  
      
  }
  printf("\n");
  
int vertices = *(p+0);
int Adjacent_vertices = *(p+1);
/*****************************************************************************************/  
  xadj_[0] = 0;
  int *r  = GetArrays(2, array, xadj_);  
  
/* nvtxs : The number of vertices.*/
# define NVTXS vertices
//# define NVTXS 6
//# define NVTXS array[0]
  idx_t nvtxs = NVTXS;

/* ncon : Number of balancing constraints, which must be at least 1.*/
  idx_t ncon = 1;

/* xadj :  Pointers to initial entries in adjacency array.*/
  //idx_t xadj[NVTXS+1] = { 0, 2, 5, 7, 9, 12, 14 };
  idx_t xadj[NVTXS+1];
  
  printf("\n");
  for (int i = 0; i < NVTXS+1; i++){
      xadj[i] = xadj_[i];
      printf("%d  %zu  %d\n", i,  xadj[i], xadj_[i]);    
  }
  printf("\n");
  
/*****************************************************************************************/  
    int *q = GetArrays(1, array, adjncy_);

/* adjncy : Adjacent vertices in consecutive index order.*/
# define NEDGES Adjacent_vertices
//# define NEDGES 7
//# define NEDGES array[1]
  //idx_t adjncy[2 * NEDGES] = {1,3,0,4,2,1,5,0,4,3,1,5,4,2};
  idx_t adjncy[2 * NEDGES];
  
  printf("\n");
  for (int i = 0; i < 2 * NEDGES; i++){
      adjncy[i] = adjncy_[i]; 
      printf("%d  %zu  %d\n", i,  adjncy[i], adjncy_[i]);    
  }
  printf("\n");
  
/*****************************************************************************************/  
/* vwgt   (NULL) : The weights of the vertices as described in Section 5.5. */
/* vsize  (NULL) : The size of the vertices for computing the total communication volume as described in Section 5.7. */
/* adjwgt (NULL) : The weights of the edges as described in Section 5.5. */

/* nparts : The number of parts requested for the partition. */
  idx_t nParts = 2;

/* tpwgts (NULL) : This is an array of size nparts×ncon that specifies the desired weight for each partition and constraint.*/
/* ubvec  (NULL) : This is an array of size ncon that specifies the allowed load imbalance tolerance for each constraint.*/
/* options NULL) : This is the array of options as described in Section 5.4*/
  
/* objval : On return, the edge cut volume of the partitioning solution. */
  idx_t objval;

/* part : On return, the partition vector for the graph.*/
  idx_t part[NVTXS];

  printf ( "\n" );
  printf ( "PARTGRAPHRECURSIVE_TEST:\n" );
  printf ( "  METIS_PartGraphRecursive partitions a graph into K parts\n" );
  printf ( "  using multilevel recursive bisection.\n" );

  int ret = METIS_PartGraphRecursive ( &nvtxs, &ncon, xadj, adjncy, NULL, NULL, NULL, &nParts, NULL, NULL, NULL, &objval, part);

  printf ( "\n" );
  printf ( "  Return code = %d\n", ret );
  printf ( "  Edge cuts for partition = %d\n", ( int ) objval );
    
  printf ( "\n" );
  printf ( "  Partition vector:\n" );
  printf ( "\n" );
  printf ( "  Node  Part\n" );
  printf ( "\n" );
  
  for ( unsigned part_i = 0; part_i < nvtxs; part_i++ ) {
      printf ( "     %d     %d\n", part_i, ( int ) part[part_i] );
  }
  
  return;
}

/******************************************************************************
  Purpose: TIMESTAMP prints the current YMDHMS date as a time stamp.
******************************************************************************/
void timestamp ( ) {
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  printf ( "%s\n", time_buffer );

  return;
# undef TIME_SIZE
}

/******************************************************************************
  Purpose: Get arrays xadj and adjncy
******************************************************************************/
int* GetArrays(int x, int* array, int* out_adj) {
    int num_edges;      // Number of vertices edges
    int l;               // count the number of nodes	 
    int counter;         // count the number of row  
    int i;
    char* line = NULL;
     
/* Open File */      
    FILE* fp;
    char* filename = "info.graph"; //  text file name
    fp = fopen(filename, "r");
    
    if (fp == NULL) {
        fprintf(stderr, "\nError opening data file\n\n");
        exit(EXIT_FAILURE);
    }
    
/* Execute subroutine 1*/       
    num_edges = 0, l = 0, counter = 0;  
    built_arrays(x, line, fp, &counter,  &num_edges, &l, out_adj);
    
    fclose(fp);
    if (line) free(line);  
       
//     printf("%d %d %d\n", l, counter, num_edges);
//     printf("\n");
//Dimension data   
 
    if (x==3) {
        array[0] = l;
        array[1] = counter;
        array[2] = num_edges;
// 	for (i = 0; i < 3; i++){
//             printf("%d   ", array[i]);    
//         }
//         printf("\n");
     }
     
   return array;
}

/******************************************************************************
  Purpose: Get array adjncy
******************************************************************************/
int built_arrays(int x, char* line, FILE* fp, int* counter, int* num_edges, int* l, int* out_adj) {
   char newString[10][10];
   int edges;
   int i, j, k,  ctr;	 
   size_t len = 0;      // An unsigned integral data type defined by several C/C++ standards,
   ssize_t read;        // same as size_t, but is a signed type that it is able to represent the number -1
      
   while ((read = getline(&line, &len, fp)) != -1) {
       if (*counter == 0) {
	 //printf("%d, %s", *counter, line);
       } else {
         //printf("%d, %s", *counter, line);
         ctr = 0, j = 0;
         for (k = 0; k <= (strlen(line)); k++) {
             if (line[k] == ' ' || line[k] == '\0'){ //if space ' ' or NULL '\0' found, assign NULL into newString[ctr]
                newString[ctr][j] = '\0';
                ctr++;  //for next word
                j = 0;  //for next word, init index to 0
             } else {
                newString[ctr][j] = line[k];
                j++;       
             } // End if 2    
         } // End For loop 1 
  
         if(x == 1 ){
         for (k = 0; k < ctr; k++) {
            edges = k + *num_edges;
             out_adj[edges] = atoi(newString[k]);
         }// End For 2 
         }
         *num_edges = *num_edges + ctr; // count Number of vertices edges
         *l = *l + 1;
          if(x == 2 ){ out_adj[*l] = *num_edges; }   
      } // End IF 1
      *counter = *counter + 1;
    } // End while
}// End Subroutine