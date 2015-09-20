//============================================================================
// Name        : any.cpp
// Author      : Vladimir Strisovsky
// Version     :
// Copyright   : Your copyright notice
// Description : unit tests for zip
//============================================================================

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <sstream>

#include "functions.hpp"


TEST_CASE("Any")
{
  Functions _;

  SECTION("AnyOf")
  {
    bool result =
      _(   From({1,2,3,4,5,6,7})
       ,   AnyOf([](int i){return i == 4;})
       );
    REQUIRE(result == true);
  }

  SECTION("AnyOf")
  {
    bool result =
      _(   From({1,2,3,4,5,6,7})
       ,   AnyOf([](int i){return i == 8;})
       );
    REQUIRE(result == false);
  }
}
