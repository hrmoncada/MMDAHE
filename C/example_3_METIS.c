/* http://people.math.sc.edu/Burkardt/cpp_src/metis_test/metis_test.cpp

  Purpose: METIS_TEST tests the METIS library.
  
Load Module
  module load gcc
  module load metis
Build with
  gcc example_3_METIS.c  -lmetis -o out
  gcc example_3_METIS.c -L/usr/lib/x86_64-linux-gnu  -o out

1. Henry metis own installation
module load gcc
$ gcc -c example_3_METIS.c -o driver.o
$ gcc -o out driver.o -L. /usr/projects/climate/hrmoncada/repos/Sources/parmetis-4.0.3/metis/build/Linux-x86_64/libmetis/libmetis.a -lm

2. Grizzly-climate metis installation
mdlgrgnu
module load metis

$ gcc -c example_3_METIS.c -o driver.o
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

int main ( );
void partgraphkway_test ( );
void timestamp ( );

int main ( ) {

  timestamp ( );
  
  printf ( "\n" );
  printf ( "METIS_TEST\n" );
  printf ( "  C version\n" );
  printf ( "  Test the METIS library for graph partitioning.\n" );

  partgraphkway_test ( );
/* Terminate. */
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
void partgraphkway_test ( ){

/*  The number of vertices. */
# define NVTXS 6
  idx_t nvtxs = NVTXS;

/* Number of balancing constraints, which must be at least 1.*/
  idx_t ncon = 1;

/*  Pointers to initial entries in adjacency array.*/
  idx_t xadj[NVTXS+1] = { 0, 2, 5, 7, 9, 12, 14 };

/* Adjacent vertices in consecutive index order.*/
# define NEDGES 7
  idx_t adjncy[2 * NEDGES] = {1,3,0,4,2,1,5,0,4,3,1,5,4,2};

/* vwgt   (NULL) : The weights of the vertices as described in Section 5.5. */
/* vsize  (NULL) : The size of the vertices for computing the total communication volume as described in Section 5.7. */
/* adjwgt (NULL) : The weights of the edges as described in Section 5.5. */

/*  The number of parts requested for the partition.*/
  idx_t nParts = 2;

/* tpwgts (NULL) : This is an array of size nparts×ncon that specifies the desired weight for each partition and constraint.*/
/* ubvec  (NULL) : This is an array of size ncon that specifies the allowed load imbalance tolerance for each constraint.*/
/* options NULL) : This is the array of options as described in Section 5.4*/

/*  On return, the edge cut volume of the partitioning solution.*/
  idx_t objval;
  
/*  On return, the partition vector for the graph.*/
  idx_t part[NVTXS];

  printf ( "\n" );
  printf ( "PARTGRAPHKWAY_TEST:\n" );
  printf ( "  METIS_PartGraphKway partitions a graph into K parts\n" );
  printf ( "  using multilevel K-way partition.\n" );

  int ret = METIS_PartGraphKway ( &nvtxs, &ncon, xadj, adjncy, NULL, NULL, NULL, &nParts, NULL, NULL, NULL, &objval, part );

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
