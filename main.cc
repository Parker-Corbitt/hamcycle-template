#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include "hamcycle.h"
#include <mpi.h> 

using namespace std;

bool graph[MAXDIM][MAXDIM];
int graphdim;
int num_procs = 1;
int proc_rank = 0;
int debug = 0;

// assumes the input is 2 integers on each line
void readfile(char *filename) {
   ifstream datafile;
   datafile.open(filename);
   if ( !datafile.is_open() ) {
      perror(filename);
      exit(1);
   }

   while (datafile) {
      int v1,v2;
      datafile >> v1;
      datafile >> v2;
      if ((v1 >= MAXDIM) || (v2 >= MAXDIM)) {
         fprintf(stderr,"Data set has too many vertices (max %d)\n", MAXDIM);
         exit(66);
      }
      graph[v1][v2] = 1; // undirected
      graph[v2][v1] = 1; // undirected
      if (v1 >= graphdim)
         graphdim = v1+1;      
      if (v2 >= graphdim)
         graphdim = v2+1;
   }
}


int main(int argc, char *argv[]) {

   if (argc != 2) {
      fprintf(stderr,"Usage: %s filename\n", argv[0]);
      exit(1);
   }
   char *filename = argv[1];

   // MPI_Init(NULL,NULL);

   // MPI_Comm_size(MPI_COMM_WORLD,&num_procs);
   // MPI_Comm_rank(MPI_COMM_WORLD,&proc_rank);

   if (debug) cout << "I am process " << proc_rank << " of " << num_procs << endl;

   readfile(filename);

   hamCycle();

   // MPI_Finalize();

   exit(0);
}
