#include "../src/calculations.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <sys/time.h>
#include "mpi.h"

int main (int argc, char const *argv[]) {

  const int     ROOT = 0;   // MPI_Comm_rank of the master process
  int           tries,      // number of iterations
                hits,       // number of tries that landed in the circle
                reduce,     // status code of the MPI_Reduce command
                rank,       // rank of this slave
                recv;       // receive buffer (used in MPI_Reduce, doesn't do anything in this context AFAIK)

  MPI_Comm      parent;     // the parent process


  // retrieve the number of tries from the arguments
  try {
    tries = atoi(argv[1]);
  } catch (...) {
    std::cout << "Failed to parse number of random points.  Please supply an integer as the first argument.";
    exit(0);
  }

  // start & say hi!
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::cout << "I'm a slave and my rank is " << rank << ".  I'm going to generate " << tries << " random points.\n";

  // seed rand
  srand(time(NULL) + rank);

  // compute the number of hits and pass to master
  MPI_Comm_get_parent(&parent);
  hits = computeHits(tries, 1);
  std::cout << "Slave " << rank << " got " << hits << " hits.\n";
  reduce = MPI_Reduce(&hits, &recv, 1, MPI_INT, MPI_SUM, ROOT, parent);
  if (reduce != MPI_SUCCESS) std::cout << "MPI_Reduce failed..";
  MPI_Finalize();

  return 0;
}