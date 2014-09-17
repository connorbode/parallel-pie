/*
 * calculations.cpp
 *
 *  Created on: Sep 14, 2014
 *      Author: connorbode
 */

#include "calculations.h"

/**
 * Generates a random decimal between 0 and 1
 */
double randomReal() {
  return double(rand()) / double(RAND_MAX);
}

/**
 * Returns true if the distance from a point to the origin is less than the radius
 */
bool ptInCircle(double x, double y, int radius) {
  double ptToOrigin = sqrt (x*x + y*y);
  return (ptToOrigin <= radius);
}

/**
 * Returns a random position within the radius
 */
double randInSquare(int radius) {
  double r = randomReal() * radius * 2;
  return (r > radius ? r - radius : r);
}

/**
 * Generates a random point within the square generated
 * by extending _radius_ in all directions from the origin.
 * Then, determines whether that point is within the circle
 * that starts at the origin and has radius _radius_.
 */
bool randomPtInCircle(int radius) {
  double randomX = randInSquare(radius);
  double randomY = randInSquare(radius);
  return ptInCircle(randomX, randomY, radius);
}

/**
 * For number of tries, determines how many points 
 * were in the circle
 */
int computeHits(int tries, int radius) {
  int hits = 0;
  for (int i = 0; i < tries; i++) {
    if (randomPtInCircle(radius)) {
      hits = hits + 1;
    }
  }
  return hits;
}

/**
 * Generates the value of pi as a function of
 * the number of random points generated and
 * the number of those points which were in a
 * circle
 */
double generatePi(int hits, int tries) {
  return 4 * double(hits) / double(tries);
}
