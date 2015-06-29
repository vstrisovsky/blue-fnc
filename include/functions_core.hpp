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

struct Functions
{
    template<typename ... _T>
    typename _ChainTypes<_T...>::ResultType operator()(_T&&... t)
    {
        typedef _ChainTypes<_T...> ChainTypes;

        typedef typename ChainTypes::TupleType type;

        type functions(std::forward<_T>(t)...);
        // todo the next lines move to container node
        bool cont = true;
        while(cont && std::get<0>(functions).hasNext())
        {
            cont = std::get<1>(functions).push(std::get<0>(functions).value(), functions, Int<1>());
        };
        std::get<1>(functions).finish(functions, Int<1>());

        return Return<typename ChainTypes::ResultType>::get(std::get<ChainTypes::size - 1>(functions));
    }
};

#endif /* _FUNCTIONS_CORE_H_ */
