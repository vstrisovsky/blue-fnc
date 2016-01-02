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

#include "functions.hpp"

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
    //std::vector<int> v = {1,3,5,67,33,56,44,45,67,76,67,789};

    Functions _;

    // _(   From({9,8,7,6,5,4,3,2,1,0})
    //  ,   Filter([](int i) {return (i % 2) == 0;})
    //  ,   Map([](int i){return i+i;})
    //  ,   ForEach([](int i){std::cout << i << "\n";})
    //  );
    // std::cout << "------\n";
    // _(   Range(1000)
    //  ,   Filter([](int i) {return (i % 2) == 0;})
    //  ,   Take(20)
    //  ,   Map([](int i){return i+i;})
    //  ,   ForEach([](int i){std::cout << i << "\n";})
    //  );
    // std::cout << "------\n";
    // _(   Range()
    //  ,   Zip(From(v))
    //  ,   Zip(Range(100))
    //  ,   ForEach([](std::tuple<int, int, int>&& v){std::cout << std::get<0>(v) << ":" << std::get<1>(v) << ":" << std::get<2>(v) << "\n";})
    //  );
    // std::cout << "------\n";
    // _(   From({A{2000}, A{3}})
    //  ,   Map(&A::value)
    //  ,   Filter([](int i){return i > 10;})
    //  ,   ForEach([](int i){std::cout << i << "\n";})
    //  );
    // std::cout << "------\n";
    // _(   From({A{2000}, A{3}})
    //  ,   Map(&A::x)
    //  ,   Filter([](int i){return i > 10;})
    //  ,   ForEach([](int i){std::cout << i << "\n";})
    //  );
    // std::cout << "------\n";
    // _(   Range(1000)
    //  ,   Drop(998)
    //  ,   ForEach([](int i){std::cout << i << "\n";})
    //  );
    //  std::cout << "------\n";
    //  _(   Range(10, 0)
    //   ,   Take(14)
    //   ,   ForEach([](int i){std::cout << i << "\n";})
    //   );
    //
    // std::cout << "------\n";
    // int sum = _(   Range(5)
    //            ,   Reduce(0, [](int a, int b){ return a + b;})
    //            );
    // std::cout << "Sum is: " << sum << "\n";
    // std::cout << "------\n";

    size_t perfCount = 10000000;

    boost::timer tm;

    std::vector<int> tv;
    tv.reserve(perfCount);
    int c = 0;
    for(size_t i = 0; i < perfCount; ++i)
    {
        int v = i * i;
        if(v%2 && perfCount/2)
        {
            tv.emplace_back(v);
        }
        ++c;
    };
    std::cout << "Raw: " << tm.elapsed() << "\n";

    std::cout << "------\n";

    tm.restart();

    auto r2 = _( range(perfCount)
               , map([](int i) {return i * i;})
               , filter([](int i){ return i % 2;})
               , drop(perfCount/2)
               , tovector<std::vector<int>>(perfCount)
               );

    std::cout << "blue-fnc: " << tm.elapsed() << "\n";

    // auto sample = []()
    // {
    //     double x = (double)rand() / RAND_MAX;
    //     double y = (double)rand() / RAND_MAX;
    //     return (x*x + y*y) < 1 ? 1 : 0;
    // };
    //
    // const int numSamples = 1000000;
    // auto count = _( Range(numSamples)
    //               , Map([sample](int){ return sample();})
    //               , Reduce(0, [](int a, int b){ return a + b;})
    //               );
    //
    // std::cout << "Pi: " << 4.0 * (double) count / (double) numSamples << "\n";

    return EXIT_SUCCESS;
}
