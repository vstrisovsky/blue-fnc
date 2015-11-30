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
    _(   Range(10)
     ,   Take(5)
     ,   ForEach([&result](int i){result << i << ",";})
    );
    REQUIRE(result.str() == "0,1,2,3,4,");
  }
  SECTION("From and take")
  {
    std::stringstream result;
    _(   From(std::string("abcdefghijkl"))
     ,   Take(5)
     ,   ForEach([&result](char i){result << i;})
    );
    REQUIRE(result.str() == "abcde");
  }
  SECTION("TakeWhile")
  {
    std::stringstream result;
    _(   Range(10)
     ,   TakeWhile([](int i){return i < 5;})
     ,   ForEach([&result](int i){result << i << ",";})
    );
    REQUIRE(result.str() == "0,1,2,3,4,");
  }
}
