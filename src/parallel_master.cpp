#include "../src/calculations.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <sys/time.h>
#include "mpi.h"

const int       ROOT = 0;                           // MPI_Comm_rank of the master process
char*           COMMAND = "build/parallel_slave.o"; // Slave command

struct timeval  start_time, // start of computation
                end_time;   // end of computation

int             tries,      // number of attempts a given process has made
                total_tries,// total number of attempts
                hits,       // number of tries which landed inside the circle
                total_hits, // total number of tries which landed inside the circle
                reduce,     // the reduce status code
                spawn,      // the spawn status code
                rank,       // the rank of a process
                num_slaves; // the number of slaves to start

char*           argzz[1];  // arguments passed to slave process

double          pi;         // the computed value of pi

long int        s_elapsed,  // the length of the computation in seconds
                ms_elapsed, // the length of the computation in milliseconds
                us_elapsed; // the length of the computation in microseconds

bool            timer_started = false;

MPI_Comm        slave_group;// the group of slaves that gets spawned
MPI_Info        spawn_info; // k-v object containing spawning info

int main (int argc, char const *argv[]) {

  // check that number of total tries is suppplied
  try {
    total_tries = atoi(argv[1]);
    num_slaves = atoi(argv[2]);
  } catch (...) {
    std::cout << "Failed to parse number of random points.  Please supply an integer as the first argument.";
    exit(0);
  }

  // start timer
  if (!timer_started) {
    timer_started = true;
    gettimeofday(&start_time, NULL);
  }

  // start computation
  MPI_Init(NULL, NULL);
  std::cout << "I'm the root process, and my rank is " << rank << "\n";

  // spawn slaves
  MPI_Info_create(&spawn_info);
  tries = total_tries / num_slaves;
  argzz[0] = (char*) malloc(256 * sizeof(char));
  sprintf(argzz[0], "%i", tries);
  std::cout << "Spawning slaves... \n";
  spawn = MPI_Comm_spawn(COMMAND, argzz, num_slaves, MPI_INFO_NULL, ROOT, MPI_COMM_SELF, &slave_group, (int*) MPI_ERRCODES_IGNORE);
  std::cout << "Spawn status code: " << spawn << "\n";

  // retrieve output from slaves
  reduce = MPI_Reduce(&hits, &total_hits, 1, MPI_INT, MPI_SUM, MPI_ROOT, slave_group);
  if (reduce != MPI_SUCCESS) std::cout << "MPI_Reduce failed..";

  // output result and time difference
  pi = generatePi(total_hits, total_tries);
  gettimeofday(&end_time, NULL);
  s_elapsed = end_time.tv_sec - start_time.tv_sec;
  ms_elapsed = end_time.tv_usec / 1000 - start_time.tv_usec / 1000;
  us_elapsed = end_time.tv_usec - start_time.tv_usec;
  std::cout << "Tries: " << total_tries << "\n";
  std::cout << "Hits: " << total_hits << "\n";
  std::cout << "PI: " << pi << "\n";
  std::cout << "Time elapsed: " << us_elapsed << " microseconds; " << ms_elapsed << " milliseconds; " << s_elapsed << " seconds\n";

  MPI_Finalize();

  return 0;
}