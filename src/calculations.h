/*
 * calculations.h
 *
 *  Created on: Sep 14, 2014
 *      Author: connorbode
 */

#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <cmath>
#include <cstdlib>
#include <iostream>
 
int computeHits(int tries, int radius);
bool ptInCircle(double x, double y, int radius);
double randInSquare(int radius);
double randomReal();
bool randomPtInCircle(int radius);
double generatePi(int hits, int tries);

#endif