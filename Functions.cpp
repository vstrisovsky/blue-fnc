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
#include <tuple>

template <typename T>
struct function_traits;

template <typename T>
struct function_traits;

// For generic types, directly use the result of the signature of its 'operator()'

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const>
// we specialize for pointers to member function
{
    enum { arity = sizeof...(Args) };
    // arity is the number of arguments.

    typedef ReturnType result_type;

    template <size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        // the i-th argument is equivalent to the i-th tuple element of a tuple
        // composed of those arguments.
    };
};

enum NodeTypeEnum
{
    eGenerator,
    eFunctor,
    eTerminator
};

template<int _Type>
struct NodeType
{
};

template<typename _Left, typename _Right, typename _Enable = void>
struct _Connection
{
    typedef typename _Left::_OutType _InType;
    typedef typename _Right::_InType _OutType;

    _Left _l;
    _Right _r;

    _Connection(_Left l, _Right r)
    : _l(l), _r(r)
    {
    }

//    _OutType apply(_InType value)
//    {
//        _r(value);
//    }
};

template<typename _Left, typename _Right>
struct _Connection<_Left, _Right, typename std::enable_if<std::is_same<NodeType<eGenerator>, typename _Left::_NodeType>::value >::type>
{
    typedef typename _Left::_OutType _InType;
    typedef typename _Right::_InType _OutType;


    _Connection(_Left l, _Right r)
    {
//        while(l._node.next())
//        {
//            r.apply(l._node.value());
//        }
    }

};

template<typename _T>
struct _Node
{
    typedef typename _T::_InType _InType;
    typedef typename _T::_OutType _OutType;
    typedef typename _T::_NodeType _NodeType;

    _T _node;

    _Node(_T node)
    : _node(node)
    {
    }
};

template<typename _Left, typename _Right>
_Connection<_Node<_Left>, _Node<_Right>> operator>>(_Node<_Left> l, _Node<_Right> r)
{
    return _Connection<_Node<_Left>, _Node<_Right>>(l,r);
}

template<typename _T>
struct _Range
{
    typedef void _InType;
    typedef _T _OutType;
    typedef NodeType<eGenerator> _NodeType;

    _T _current, _to, _value;
    _Range(_T first, _T last)
    : _current(first), _to(last), _value(first)
    {
    }

    bool next()
    {
        bool result = _current < _to;
        _value = _current;
        ++_current;
        return result;
    }

    _T value() const
    {
        return _value;
    }
};

template<typename _T>
_Node<_Range<_T>> range(_T first, _T last)
{
    return _Node<_Range<_T>>(_Range<_T>(first, last));
}

template<typename _Fnc>
struct _Terminator
{
    typedef function_traits<decltype(&_Fnc::operator())> _InTraits;
    typedef typename _InTraits::template arg<0>::type _InType;
    typedef void _OutType;
    typedef NodeType<eTerminator> _NodeType;

    _Fnc _fnc;
    _Terminator(_Fnc fnc)
    : _fnc(fnc)
    {

    }

    void operator()(_InType v)
    {
        _fnc(v);
    }
};

template<typename _Fnc>
struct _Functor
{
    typedef function_traits<decltype(&_Fnc::operator())> _InTraits;
    typedef typename _InTraits::template arg<0>::type _InType;
    typedef typename _InTraits::result_type _OutType;
    typedef NodeType<eFunctor> _NodeType;

    _Fnc _fnc;
    _Functor(_Fnc fnc)
    : _fnc(fnc)
    {

    }

    _OutType operator()(_InType v)
    {
        _fnc(v);
    }
};

template<typename _Fnc>
_Node<_Functor<_Fnc>> Map(_Fnc fnc)
{
    return _Node<_Functor<_Fnc>>(_Functor<_Fnc>(fnc));
}

template<typename _Fnc>
_Node<_Terminator<_Fnc>> ForEach(_Fnc fnc)
{
    return _Node<_Terminator<_Fnc>>(fnc);
}

int main(void)
{
    range(0, 100) >> Map([](int i){ return 2 * i;}) >> ForEach([](int i){std::cout << "value: " << i << "\n";});
    return EXIT_SUCCESS;
}
