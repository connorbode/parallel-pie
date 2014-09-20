#include "../src/calculations.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <sys/time.h>
#include "mpi.h"

int main (int argc, char const *argv[]) {

  const int       ROOT = 0;   // MPI_Comm_rank of the master process

  struct timeval  start_time, // start of computation
                  end_time;   // end of computation

  int             tries,      // number of attempts a given process has made
                  total_tries,// total number of attempts
                  hits,       // number of tries which landed inside the circle
                  total_hits, // total number of tries which landed inside the circle
                  reduce,     // the reduce status code
                  size,       // the size of the comm world
                  rank;       // the rank of a process

  double          pi;         // the computed value of pi

  long int        s_elapsed,  // the length of the computation in seconds
                  ms_elapsed; // the length of the computation in milliseconds

  bool            timer_started = false;

  // check that number of total tries is suppplied
  try {
    total_tries = atoi(argv[1]);
  } catch (...) {
    std::cout << "Failed to parse number of random points.  Please supply an integer as the first argument.";
    exit(0);
  }

  // seed rand
  srand(time(NULL));

  // start timer
  if (!timer_started) {
    timer_started = true;
    gettimeofday(&start_time, NULL);
  }

  // start computation
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::cout << "I'm a process, and my rank is " << rank << "\n";

  // run this processes' share of the computation
  tries = total_tries / size;
  hits = computeHits(tries, 1);

  // reduce all computations and generate pi
  reduce = MPI_Reduce(&hits, &total_hits, 1, MPI_INT, MPI_SUM, ROOT, MPI_COMM_WORLD);
  if (reduce != MPI_SUCCESS) std::cout << "MPI_Reduce failed..";

  // output result and time difference
  if (rank == ROOT) {
    pi = generatePi(total_hits, total_tries);
    gettimeofday(&end_time, NULL);
    s_elapsed = end_time.tv_sec - start_time.tv_sec;
    ms_elapsed = end_time.tv_usec / 1000 - start_time.tv_usec / 1000;
    us_elapsed = end_time.tv_usec - start_time.tv_usec;
    std::cout << "Tries: " << total_tries << "\n";
    std::cout << "Hits: " << total_hits << "\n";
    std::cout << "PI: " << pi << "\n";
    std::cout << "Time elapsed: " << ms_elapsed << " milliseconds; " << s_elapsed << " seconds\n";
  }

  MPI_Finalize();

  return 0;
}