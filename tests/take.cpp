//============================================================================
// Name        : take.cpp
// Author      : Vladimir Strisovsky
// Version     :
// Copyright   : Your copyright notice
// Description : unit tests for take
//============================================================================

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <sstream>

#include "functions.hpp"
#include "test_result.hpp"

TEST_CASE("Take")
{
  Functions _;

  SECTION("Range and take")
  {
    TestResult result =
    _(   range(10)
     ,   take(5)
     ,   tovector<TestResult>()
    );
    REQUIRE(result == TestResult({0,1,2,3,4}));
  }
  SECTION("From and take")
  {
    TestStringResult result =
    _(   from(std::string("abcdefghijkl"))
     ,   take(5)
     ,   tovector<TestStringResult>()
    );
    REQUIRE(result == "abcde");
  }
  SECTION("TakeWhile")
  {
    TestResult result =
    _(   range(10)
     ,   takewhile([](int i){return i < 5;})
     ,   tovector<TestResult>()
    );
    REQUIRE(result == TestResult({0,1,2,3,4}));
  }
}
