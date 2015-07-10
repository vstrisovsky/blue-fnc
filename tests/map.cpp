//============================================================================
// Name        : map.cpp
// Author      : Vladimir Strisovsky
// Version     :
// Copyright   : Your copyright notice
// Description : unit tests for map
//============================================================================

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <sstream>

#include "functions.hpp"

template<typename _T>
int pow(int v)
{
  return v * v;
}

template<typename _T>
struct Pow
{
int operator()(_T v)
{
  return v * v;
}
};

struct A
{
  int v;
  int get() const
  {
    return v;
  }
};

TEST_CASE("Map")
{
  Functions _;

  SECTION("from char to another char")
  {
    std::stringstream result;
    _(   From(std::string("abcde"))
     ,   Map([](char ch)  { return ch + 1;})
     ,   ForEach([&result](char ch){result << ch;})
    );
    REQUIRE(result.str() == "bcdef");
  }

  SECTION("from char to int")
  {
    std::stringstream result;
    _(   From(std::string("abcde"))
     ,   Map([](char ch) -> int { return ch - 'a';})
     ,   ForEach([&result](int i){result << i << ",";})
    );
    REQUIRE(result.str() == "0,1,2,3,4,");
  }

  SECTION("map via function")
  {
    std::stringstream result;
    _(   From({0,1,2,3,4})
     ,   Map(pow<int>)
     ,   ForEach([&result](int i){result << i << ",";})
    );
    REQUIRE(result.str() == "0,1,4,9,16,");
  }

  SECTION("map via function object")
  {
    std::stringstream result;
    _(   From({0,1,2,3,4})
     ,   Map(Pow<int>())
     ,   ForEach([&result](int i){result << i << ",";})
    );
    REQUIRE(result.str() == "0,1,4,9,16,");
  }

  SECTION("map via pointer to member variable")
  {
    std::stringstream result;
    _(   From({A{0},A{1},A{2},A{3},A{4}})
     ,   Map(&A::v)
     ,   ForEach([&result](int i){result << i << ",";})
    );
    REQUIRE(result.str() == "0,1,2,3,4,");
  }

  SECTION("map via pointer to member variable")
  {
    std::stringstream result;
    _(   From({A{0},A{1},A{2},A{3},A{4}})
     ,   Map(&A::get)
     ,   ForEach([&result](int i){result << i << ",";})
    );
    REQUIRE(result.str() == "0,1,2,3,4,");
  }
}
