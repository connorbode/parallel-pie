#include "../src/calculations.h"
#include <iostream>
#include <time.h>

int main (int argc, char const *argv[]) {
  srand(time(NULL));
  int tries = 10000000;
  int hits = computeHits(tries, 1);
  std::cout << generatePi(hits, tries) << "\n";
  return 0;
}