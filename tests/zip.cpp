//============================================================================
// Name        : zip.cpp
// Author      : Vladimir Strisovsky
// Version     :
// Copyright   : Your copyright notice
// Description : unit tests for zip
//============================================================================

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <sstream>

#include "functions.hpp"


TEST_CASE("Zip")
{
  Functions _;

  SECTION("String + Infinite range")
  {
    std::stringstream result;
    _(   From(std::string("abcd"))
     ,   Zip(Range())
     ,   ForEach([&result](std::tuple<char, int>&& i)
         {
           result << "(" << std::get<0>(i) << "," << std::get<1>(i) << ")";
        })
    );
    REQUIRE(result.str() == "(a,0)(b,1)(c,2)(d,3)");
  }
  SECTION("Infinite range + String")
  {
    std::stringstream result;
    _(   Range()
     ,   Zip(From(std::string("abcd")))
     ,   ForEach([&result](std::tuple<int, char>&& i)
         {
           result << "(" << std::get<0>(i) << "," << std::get<1>(i) << ")";
        })
    );
    REQUIRE(result.str() == "(0,a)(1,b)(2,c)(3,d)");
  }
}
