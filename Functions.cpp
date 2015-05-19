//============================================================================
// Name        : Functions.cpp
// Author      : Vladimir Strisovsky
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <typeinfo>

#include <boost/timer.hpp>

#include "functions.h"

struct A
{
    int value() const
    {
        return x * 5;
    }

    int x;
};

int main(void)
{
    boost::timer tm;

    std::vector<int> v = {1,3,5,67,33,56,44,45,67,76,67,789};

    Functions _;

    _(   From({9,8,7,6,5,4,3,2,1,0})
     ,   Filter([](int i) {return (i % 2) == 0;})
     ,   Map([](int i){return i+i;})
     ,   ForEach([](int i){std::cout << i << "\n";})
     );
    std::cout << "------\n";
    _(   Range(0, 1000)
     ,   Filter([](int i) {return (i % 2) == 0;})
     ,   Take(20)
     ,   Map([](int i){return i+i;})
     ,   ForEach([](int i){std::cout << i << "\n";})
     );
    std::cout << "------\n";
    _(   Range(0)
     ,   Zip(From(v))
     ,   Zip(Range(100))
     ,   ForEach([](std::tuple<int, int, int>&& v){std::cout << std::get<0>(v) << ":" << std::get<1>(v) << ":" << std::get<2>(v) << "\n";})
     );
    std::cout << "------\n";
    _(   From({A{2000}, A{3}})
     ,   Map(&A::value)
     ,   Filter([](int i){return i > 10;})
     ,   ForEach([](int i){std::cout << i << "\n";})
     );
    std::cout << "------\n";
    _(   From({A{2000}, A{3}})
     ,   Map(&A::x)
     ,   Filter([](int i){return i > 10;})
     ,   ForEach([](int i){std::cout << i << "\n";})
     );
    std::cout << "------\n";
    _(   Range(0, 1000)
     ,   Drop(998)
     ,   ForEach([](int i){std::cout << i << "\n";})
     );
    std::cout << "------\n";

    std::cout << tm.elapsed() << "\n";

    return EXIT_SUCCESS;
}
