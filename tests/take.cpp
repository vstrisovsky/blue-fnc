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


TEST_CASE("Take")
{
  Functions _;

  SECTION("Range and take")
  {
    std::stringstream result;
    _(   range(10)
     ,   take(5)
     ,   foreach([&result](int i){result << i << ",";})
    );
    REQUIRE(result.str() == "0,1,2,3,4,");
  }
  SECTION("From and take")
  {
    std::stringstream result;
    _(   from(std::string("abcdefghijkl"))
     ,   take(5)
     ,   foreach([&result](char i){result << i;})
    );
    REQUIRE(result.str() == "abcde");
  }
  SECTION("TakeWhile")
  {
    std::stringstream result;
    _(   range(10)
     ,   takewhile([](int i){return i < 5;})
     ,   foreach([&result](int i){result << i << ",";})
    );
    REQUIRE(result.str() == "0,1,2,3,4,");
  }
}
