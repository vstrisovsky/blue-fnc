//============================================================================
// Name        : Functions.cpp
// Author      : Vladimir Strisovsky
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <sstream>

#include "functions.hpp"


TEST_CASE("From generators")
{
  Functions _;

  SECTION("From+initializer list")
  {
    std::stringstream result;
    _(   From({9,8,7,6,5,4,3,2,1,0})
     ,   ForEach([&result](int i){result << i << ",";})
    );
    CAPTURE(result.str());
    REQUIRE(result.str() == "9,8,7,6,5,4,3,2,1,0,");
  }
}

TEST_CASE("Range generators")
{
  Functions _;

  SECTION("Count")
  {
    std::stringstream result;
    _(   Range(10)
     ,   ForEach([&result](int i){result << i << ",";})
    );
    CAPTURE(result.str());
    REQUIRE(result.str() == "0,1,2,3,4,5,6,7,8,9,");
  }
  SECTION("Start, End")
  {
    std::stringstream result;
    _(   Range(0, 10)
     ,   ForEach([&result](int i){result << i << ",";})
    );
    CAPTURE(result.str());
    REQUIRE(result.str() == "0,1,2,3,4,5,6,7,8,9,");
  }
  SECTION("Start, End, Step")
  {
    std::stringstream result;
    _(   Range(0, 10, 2)
     ,   ForEach([&result](int i){result << i << ",";})
    );
    CAPTURE(result.str());
    REQUIRE(result.str() == "0,2,4,6,8,");
  }
  SECTION("Infinite")
  {
    std::stringstream result;
    _(   Range()
     ,   Take(10)
     ,   ForEach([&result](int i){result << i << ",";})
    );
    CAPTURE(result.str());
    REQUIRE(result.str() == "0,1,2,3,4,5,6,7,8,9,");
  }
  SECTION("Start, End, Negative step")
  {
    std::stringstream result;
    _(   Range(10, 0, -1)
     ,   ForEach([&result](int i){result << i << ",";})
    );
    CAPTURE(result.str());
    REQUIRE(result.str() == "10,9,8,7,6,5,4,3,2,1,");
  }
}
