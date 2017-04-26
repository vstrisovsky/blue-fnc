//============================================================================
// Name        : range.cpp
// Author      : Vladimir Strisovsky
// Version     :
// Copyright   : Your copyright notice
// Description : unit tests for range
//============================================================================

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <sstream>

#include "functions.hpp"
#include "test_result.hpp"

TEST_CASE("Range generators")
{
  Functions _;

  SECTION("Count")
  {
    TestResult result =
    _(   range(10)
     ,   tovector<TestResult>()
    );
    REQUIRE(result == TestResult({0,1,2,3,4,5,6,7,8,9}));
  }
  SECTION("Start, End")
  {
    TestResult result =
    _(   range(0, 10)
     ,   tovector<TestResult>()
    );
    REQUIRE(result == TestResult({0,1,2,3,4,5,6,7,8,9}));
  }
  SECTION("Start, End, Step")
  {
    TestResult result =
    _(   range(0, 10, 2)
     ,   tovector<TestResult>()
    );
    REQUIRE(result == TestResult({0,2,4,6,8}));
  }
  SECTION("Infinite")
  {
    TestResult result =
    _(   range()
     ,   take(10)
     ,   tovector<TestResult>()
    );
    REQUIRE(result == TestResult({0,1,2,3,4,5,6,7,8,9}));
  }
  SECTION("Start, End, Negative step")
  {
    TestResult result =
    _(   range(10, 0, -1)
     ,   tovector<TestResult>()
    );
    REQUIRE(result == TestResult({10,9,8,7,6,5,4,3,2,1}));
  }
}
