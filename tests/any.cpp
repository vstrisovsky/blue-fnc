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
      _(   from({1,2,3,4,5,6,7})
       ,   anyof([](int i){return i == 4;})
       );
    REQUIRE(result == true);
  }

  SECTION("AnyOf")
  {
    bool result =
      _(   from({1,2,3,4,5,6,7})
       ,   anyof([](int i){return i == 8;})
       );
    REQUIRE(result == false);
  }
}

TEST_CASE("All")
{
  Functions _;

  SECTION("AllOf")
  {
    bool result =
      _(   from({1,2,3,4,5,6,7})
       ,   anyof([](int i){return i > 0;})
       );
    REQUIRE(result == true);
  }

  SECTION("AllOf")
  {
    bool result =
      _(   from({1,2,3,4,5,6,7})
       ,   anyof([](int i){return i == 8;})
       );
    REQUIRE(result == false);
  }
}

TEST_CASE("None")
{
  Functions _;

  SECTION("NoneOf")
  {
    bool result =
      _(   from({1,2,3,4,5,6,7})
       ,   anyof([](int i){return i == 0;})
       );
    REQUIRE(result == true);
  }

  SECTION("NoneOf")
  {
    bool result =
      _(   from({1,2,3,4,5,6,7})
       ,   noneof([](int i){return i == 3;})
       );
    REQUIRE(result == false);
  }
}
