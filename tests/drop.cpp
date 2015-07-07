//============================================================================
// Name        : drop.cpp
// Author      : Vladimir Strisovsky
// Version     :
// Copyright   : Your copyright notice
// Description : unit tests for drop
//============================================================================

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <sstream>

#include "functions.hpp"


TEST_CASE("Drop")
{
  Functions _;

  SECTION("Range and drop")
  {
    std::stringstream result;
    _(   Range(10)
     ,   Drop(5)
     ,   ForEach([&result](int i){result << i << ",";})
    );
    REQUIRE(result.str() == "5,6,7,8,9,");
  }
  SECTION("From and drop")
  {
    std::stringstream result;
    _(   From(std::string("abcdefghijkl"))
     ,   Drop(5)
     ,   ForEach([&result](char i){result << i;})
    );
    REQUIRE(result.str() == "fghijkl");
  }
}
