#ifndef _FUNCTIONS_CORE_H_
#define _FUNCTIONS_CORE_H_

#include <tuple>
#include <type_traits>

struct Empty{};

template<int I>
struct Int
{
    static const int i = I;

    typedef Int<i-1> Prev;
    typedef Int<i+1> Next;
};

enum class StepType
{
    eGenerator,
    eTransformator,
    eFilter,
    eLimiter,
    eTerminator,
    eReducer
};

template<typename _T, StepType = _T::stepType>
struct _ResultType
{
    typedef void ResultType;
};

template<typename _T>
struct _ResultType<_T, StepType::eReducer>
{
    typedef typename _T::ResultType ResultType;
};

template<typename... _T>
struct _ChainTypes
{
    typedef std::tuple<_T...> TupleType;
    static const int size = std::tuple_size<TupleType>::value;
    typedef typename std::tuple_element< size - 1, TupleType>::type TailType;
    typedef typename _ResultType<TailType>::ResultType ResultType;
};

template<typename _T>
struct Return
{
    template<typename _Node>
    static _T get(_Node& node)
    {
        return std::move(node.get());
    }
};

template<>
struct Return<void>
{
    template<typename _Node>
    static void get(_Node&)
    {
    }
};

template<int _Index, typename _Functions>
void iterate(_Functions& f)
{
    bool cont = true;
    while(cont && std::get<_Index>(f).hasNext())
    {
        cont = std::get<_Index+1>(f).push(std::get<_Index>(f).value(), f, Int<_Index+1>());
    };
    std::get<_Index+1>(f).finish(f, Int<_Index+1>());
}


struct Functions
{
    template<typename ... _T>
    typename _ChainTypes<_T...>::ResultType operator()(_T&&... t)
    {
        typedef _ChainTypes<_T...> ChainTypes;

        typedef typename ChainTypes::TupleType type;

        type functions(std::forward<_T>(t)...);

        iterate<0>(functions);

        return Return<typename ChainTypes::ResultType>::get(std::get<ChainTypes::size - 1>(functions));
    }
};

#endif /* _FUNCTIONS_CORE_H_ */
