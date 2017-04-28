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

TEST_CASE("Repeatedly generators")
{
  Functions _;

  SECTION("Return constant")
  {
    TestResult result =
        _(   repeatedly([]{return 1;})
         ,   take(3)
         ,   into<TestResult>()
        );
    REQUIRE(result == TestResult({1,1,1}));
  }
}

TEST_CASE("Repeat generators")
{
  Functions _;

  SECTION("Return constant")
  {
    TestResult result =
    _(   repeat(1)
     ,   take(3)
     ,   into<TestResult>()
    );
    REQUIRE(result == TestResult({1,1,1}));
  }
}
