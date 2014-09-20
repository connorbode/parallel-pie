#include "../src/calculations.h"
#include <iostream>
#include <sys/time.h>

int main (int argc, char const *argv[]) {

  struct timeval start_time, end_time;
  int tries, hits;
  long int s_elapsed, ms_elapsed;

  // check that number of random pts is supplied
  try {
    tries = atoi(argv[1]);
  } catch (...) {
    std::cout << "Failed to parse number of random points.  Please supply an integer as the first argument.";
    exit(0);
  }

  // seed rand
  srand(time(NULL));

  // start timer
  gettimeofday(&start_time, NULL);

  // generate pi
  hits = computeHits(tries, 1);
  std::cout << "Tries: " << tries << "\n";
  std::cout << "Hits: " << hits << "\n";
  std::cout << "PI: " << generatePi(hits, tries) << "\n";

  // end timer
  gettimeofday(&end_time, NULL);

  // output time difference
  s_elapsed = end_time.tv_sec - start_time.tv_sec;
  ms_elapsed = (end_time.tv_usec / 1000 + end_time.tv_sec * 1000) - (start_time.tv_usec / 1000 + start_time.tv_sec * 1000);
  std::cout << "Time elapsed: " << ms_elapsed << " milliseconds; " << s_elapsed << " seconds\n";

  return 0;
}