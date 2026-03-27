#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <mpi.h> 
#include "hamcycle.h"

using namespace std;

// shared global path for efficiency
int *path = NULL;

bool isValidStep(int n, int pos) {
   if (graph[path[pos-1]][n] == 0) {
      return false;
   }

   for (int i = 0; i < pos; i++) {
      if (path[i] == n)
         return false;
   }
   return true;
}

bool recursiveHam(int pos, int proc_rank, int num_procs) {
   // If all vertices are included in Hamiltonian Cycle
   if (pos == graphdim) {
      // can I get from end of path back to beginning?
      return(graph[path[pos-1]][ path[0]] == 1);  
   }
   
   for (int n = 1; n < graphdim; n++) {
      if (isValidStep(n, pos)) { //Check if this vertex can be added to Hamiltonian Cycle
         path[pos] = n;
         //recurse to construct rest of the path
         if (recursiveHam (pos+1,proc_rank,num_procs) == true)
            return true;
         path[pos] = -1; //remove vertex if it doesn’t lead to the solution
      }
   }
   return false;
}


void displaytheSolution() {
   cout<<"Hamiltonian Cycle Path: ";
   for (int i = 0; i < graphdim; i++)
      cout<<path[i]<<" ";
   cout<< path[0]<<endl;
}


void printMatrix() {
   for (int row=0; row < graphdim; ++row) {
      for (int col=0; col < graphdim; ++col) {
         if (graph[row][col])
            cout << row << " <--> " << col << endl;
      }
   }
}


bool hamCycle() {
   path = new int[graphdim];
   for (int i = 0; i < graphdim; i++) {
      path[i] = -1;
   }
   
   //put vertex 0 as the first vertex in the path. If there is a Hamiltonian Cycle, then the path can be 
   //started from any point
   //of the cycle as the graph is undirected
   path[0] = 0;
   if (debug) printMatrix();

   cout<<proc_rank << "/" << num_procs << ": ";
   if (recursiveHam(1,proc_rank,num_procs) == false) {
      cout << "Hamiltonian Cycle does not exist\n";
      return false;
   } 
   displaytheSolution();
   return true;
}
