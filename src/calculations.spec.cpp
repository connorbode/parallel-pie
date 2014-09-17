
#define BOOST_TEST_MODULE Unit
#include <boost/test/included/unit_test.hpp>
#include "../src/calculations.h"

BOOST_AUTO_TEST_CASE(randomRealTest) {
  double rando;
  for (int i = 0; i < 1000; i++) {
    rando = randomReal();
    BOOST_CHECK(rando >= 0);
    BOOST_CHECK(rando <= 1);
  }
}

BOOST_AUTO_TEST_CASE(ptInCircleTest) {
  BOOST_CHECK(ptInCircle(2,2,2) == false);
  BOOST_CHECK(ptInCircle(-2,-2,2) == false);
  BOOST_CHECK(ptInCircle(2,0,2) == true);
  BOOST_CHECK(ptInCircle(0,-2,2) == true);
}

BOOST_AUTO_TEST_CASE(randInSquareTest) {
  double rando;
  int radius = 1;
  for (int i = 0; i < 1000; i++) {
    rando = randInSquare(radius);
    BOOST_CHECK(rando <= radius);
    BOOST_CHECK(rando >= -radius);
  }
}

BOOST_AUTO_TEST_CASE(randomPtInCircleTest) {
  bool hasTrue = false;
  bool hasFalse = false;
  bool result;
  for (int i = 0; i < 1000; i++) {
    result = randomPtInCircle(1);
    if (result) {
      hasTrue = true;
    } else {
      hasFalse = true;
    }
  }
  BOOST_CHECK(hasTrue);
  BOOST_CHECK(hasFalse);
}
