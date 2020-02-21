/*
The end of any string is marked by the ASCII value 0 (the null character), which is represented in C as '\0'
The end-of-line is represented by the newline character, which is represented in C as '\n'.     
 Double quotes (") are for strings, which are sequences of characters. Single quotes (') are for individual characters.  
 */


//#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int built_arrays();
int GetArrays(); 
//int GetArrays2(); 
//#define GetArrays main  // Rename the main program name 

/******************************************************************************
  Purpose: Main Program 
******************************************************************************/
int main ( ) {
  int i;
  
/* Arrays */      
  int adjncy[] = {};   // Declare and empty 1D array: Adjacent vertices in consecutive index order {1,3,0,4,2,1,5,0,4,3,1,5,4,2}  
  int xadj[] = {};     // Declare and empty 1D array: Pointers to initial entries in adjacency array {0, 2, 5, 7, 9, 12, 14} 
  int array[] = {}; 

 GetArrays(1,  array , adjncy);

  printf("\n");
  for (i = 0; i < 14; i++){
      printf("%d %d\n", i,  adjncy[i]);    
  }
  printf("\n");
  
  xadj[0] = 0;
 GetArrays(2,  array, xadj);
  
  
  printf("\n");
  for (i = 0; i < 7; i++){
      printf("%d %d\n", i,  xadj[i]);    
  }
  printf("\n");

//Dimension data   
//    int l =   array2[0] ;
//    int  counter = array2[1];
//    int num_edges = array2[2]; 
     
//     printf("%d %d %d\n", l, counter, num_edges);
//     printf("\n");
  
  exit(EXIT_SUCCESS);
  return 0;
}  

/******************************************************************************
  Purpose: Get arrays xadj and adjncy
******************************************************************************/
int GetArrays(int x,  int array[], int* out_adj) {
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
// //    int array[3]; 
//     if (x==2) {
//         array[0] = l;
//         array[1] = counter;
//         array[2] = num_edges;
//      }
//      
   return 0;
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