#include "../src/calculations.h"
#include <iostream>
#include <sys/time.h>

int main (int argc, char const *argv[]) {

  struct timeval start_time, end_time;
  int tries, hits;
  long int s_elapsed, ms_elapsed, us_elapsed;

  // check that number of random pts is supplied
  try {
    tries = std::stoi(argv[1]);
  } catch (const std::invalid_argument& e) {
    std::cout << "Failed to parse number of random points.  Please supply an integer as the first argument.";
    exit(0);
  }

  // seed rand
  srand(time(NULL));

  // start timer
  gettimeofday(&start_time, NULL);

  // generate pi
  hits = computeHits(tries, 1);
  std::cout << generatePi(hits, tries) << "\n";

  // end timer
  gettimeofday(&end_time, NULL);

  // output time difference
  s_elapsed = end_time.tv_sec - start_time.tv_sec;
  ms_elapsed = end_time.tv_usec / 1000 - start_time.tv_usec / 1000;
  us_elapsed = end_time.tv_usec - start_time.tv_usec;
  std::cout << "Time elapsed: " << us_elapsed << " microseconds; " << ms_elapsed << " milliseconds; " << s_elapsed << " seconds\n";

  return 0;
}