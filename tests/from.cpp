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

  SECTION("Initializer list")
  {
    std::stringstream result;
    _(   From({9,8,7,6,5,4,3,2,1,0})
     ,   ForEach([&result](int i){result << i << ",";})
    );
    REQUIRE(result.str() == "9,8,7,6,5,4,3,2,1,0,");
  }

  SECTION("Vector")
  {
    std::stringstream result;
    _(   From(std::vector<int>({9,8,7,6,5,4,3,2,1,0}))
     ,   ForEach([&result](int i){result << i << ",";})
    );
    REQUIRE(result.str() == "9,8,7,6,5,4,3,2,1,0,");
  }

  SECTION("Iterators")
  {
    std::vector<int> c({9,8,7,6,5,4,3,2,1,0});
    std::stringstream result;
    _(   From(c.begin(), c.end())
     ,   ForEach([&result](int i){result << i << ",";})
    );
    REQUIRE(result.str() == "9,8,7,6,5,4,3,2,1,0,");
  }

  SECTION("Set")
  {
    std::stringstream result;
    _(   From(std::set<int>({9,8,7,6,5,4,3,2,1,0}))
     ,   ForEach([&result](int i){result << i << ",";})
    );
    REQUIRE(result.str() == "0,1,2,3,4,5,6,7,8,9,");
  }

}
