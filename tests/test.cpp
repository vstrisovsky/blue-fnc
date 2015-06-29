//============================================================================
// Name        : Functions.cpp
// Author      : Vladimir Strisovsky
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>

#include "functions.hpp"


TEST_CASE("Test", "[tag]")
{
  bool b = true;
  REQUIRE( b == true );
}
