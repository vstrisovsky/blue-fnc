//============================================================================
// Name        : from.cpp
// Author      : Vladimir Strisovsky
// Version     :
// Copyright   : Your copyright notice
// Description : unit tests for from
//============================================================================

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <sstream>

#include "functions.hpp"
#include "test_result.hpp"

TEST_CASE("From generators")
{
  Functions _;

  SECTION("Initializer list")
  {
    TestResult result =
    _(   from({9,8,7,6,5,4,3,2,1,0})
     ,   tovector<TestResult>()
    );
    REQUIRE(result == TestResult({9,8,7,6,5,4,3,2,1,0}));
  }

  SECTION("Vector")
  {
    TestResult result =
    _(   from(std::vector<int>({9,8,7,6,5,4,3,2,1,0}))
     ,   tovector<TestResult>()
    );
    REQUIRE(result == TestResult({9,8,7,6,5,4,3,2,1,0}));
  }

  SECTION("Iterators")
  {
    std::vector<int> c({9,8,7,6,5,4,3,2,1,0});
    TestResult result =
    _(   from(c.begin(), c.end())
     ,   tovector<TestResult>()
    );
    REQUIRE(result == TestResult({9,8,7,6,5,4,3,2,1,0}));
  }

  SECTION("Set")
  {
    TestResult result =
    _(   from(std::set<int>({9,8,7,6,5,4,3,2,1,0}))
     ,   tovector<TestResult>()
    );
    REQUIRE(result == TestResult({0,1,2,3,4,5,6,7,8,9}));
  }

  SECTION("Array")
  {
    int arr[] = {9,8,7,6,5,4,3,2,1,0};
    TestResult result =
    _(   fromArray(arr)
     ,   tovector<TestResult>()
    );
    REQUIRE(result == TestResult({9,8,7,6,5,4,3,2,1,0}));
  }

  SECTION("String")
  {
    TestResult result =
    _(   fromArray("ABC")
     ,   tovector<TestResult>()
    );
    REQUIRE(result == TestResult({65,66,67,0}));
  }
}
