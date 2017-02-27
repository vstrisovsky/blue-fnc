#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "functions_core.hpp"

#include <initializer_list>
#include <limits>

template<typename _T>
struct _Range
{
    static const StepType stepType = StepType::eGenerator;
    typedef Empty InType;
    typedef _T OutType;
    _T _start, _end, _step, _i;
    bool _dec;

    _Range(_T start, _T end)
    : _Range(start, end, _T(start > end ? -1 : 1))
    {
    }

    _Range(_T start, _T end, _T step)
    : _start(start), _end(end), _step(step)
    , _i(start), _dec(start > end)
    {
    }

    bool hasNext() const
    {
        return _dec ? _i > _end : _end > _i;
    }

    _T value()
    {
        _T result = _i;
        _i += _step;
        return result;
    }
};


template<typename _T>
_Range<_T> range(_T start, _T end, _T step)
{
    return _Range<_T>(start, end, step);
}

template<typename _T>
_Range<_T> range(_T start, _T end)
{
    return _Range<_T>(start, end);
}

template<typename _T>
_Range<_T> range(_T count)
{
    return _Range<_T>(_T(), count);
}

template<typename _T = int>
_Range<_T> range()
{
    return _Range<_T>(_T(), std::numeric_limits<_T>::max());
}

template<typename _Fnc>
struct _Repeatedly
{
    static const StepType stepType = StepType::eGenerator;
    typedef Empty InType;
    typedef typename ReturnType<_Fnc>::type OutType;
    _Fnc mFnc;

    _Repeatedly(_Fnc&& fnc)
    : mFnc(fnc)
    {
    }

    bool hasNext() const
    {
        return true;
    }

    OutType value()
    {
        return mFnc();
    }
};

template<typename _Fnc>
_Repeatedly<_Fnc> repeatedly(_Fnc&& fnc)
{
    return _Repeatedly<_Fnc>(std::move(fnc));
}

template<typename _T>
struct _FromValueType
{
    typedef typename _T::value_type type;
};

template<typename _T>
struct _FromValueType<const _T*>
{
    typedef _T type;
};

template<typename _T>
struct _From
{
    static const StepType stepType = StepType::eGenerator;
    typedef Empty InType;
    typedef typename _FromValueType<_T>::type OutType;
    _T _start, _end;
    _From(_T start, _T end)
    : _start(start), _end(end)
    {
    }

    bool hasNext() const
    {
        return _start != _end;
    }

    OutType value()
    {
        return *(_start++);
    }
};

template<typename _T>
_From<typename _T::const_iterator> from(const _T& coll)
{
    return _From<typename _T::const_iterator>(std::begin(coll), std::end(coll));
}

template<typename _T>
_From<typename std::initializer_list<_T>::const_iterator> from(std::initializer_list<_T>&& coll)
{
    return _From<typename std::initializer_list<_T>::const_iterator>(coll.begin(), coll.end());
}

template<typename _T>
_From<_T> from(_T start, _T end)
{
    return _From<_T>(start, end);
}

template<std::size_t _Count>
_From<const char*> fromArray(char(&arr)[_Count])
{
    return _From<const char*>(arr, arr + _Count - 1);
}

template<typename _T, std::size_t _Count>
_From<const _T*> fromArray(_T(&arr)[_Count])
{
    return _From<const _T*>(arr, arr + _Count);
}

template<typename _Gen>
struct _Zip
{
    static const StepType stepType = StepType::eTransformator;
    typedef Empty InType;
     _Gen _gen;
    _Zip(_Gen&& gen)
    : _gen(gen)
    {
    }

    bool hasNext() const
    {
        return _gen.hasNext();
    }

    typename _Gen::OutType value()
    {
        return _gen.value();
    }

    template<typename _T, typename _F, typename _I>
    bool push(_T&& v, _F& functions, _I)
    {
        typedef typename _I::Next Next;
        return hasNext() ? std::get<_I::i+1>(functions).push(std::make_tuple(std::move(v), value()), functions, Next()) : false;
    }

    template<typename ... _T, typename _F, typename _I>
    bool push(std::tuple<_T...>&& v, _F& functions, _I)
    {
        typedef typename _I::Next Next;
        return hasNext() ? std::get<_I::i+1>(functions).push(std::tuple_cat(std::move(v), std::make_tuple(value())), functions, Next()) : false;
    }

    template<typename _F, typename _I>
    void finish(_F& functions, _I)
    {
    }

};

template<typename _Gen>
_Zip<_Gen> zip(_Gen&& gen)
{
    return _Zip<_Gen>(std::move(gen));
}

template<typename _Fnc, typename _Enable = void>
struct _Map
{
    static const StepType stepType = StepType::eTransformator;
    _Fnc _fnc;
    _Map(_Fnc&& fnc)
    : _fnc(fnc)
    {
    }

    template<typename _T, typename _F, typename _I>
    bool push(_T&& v, _F& functions, _I i)
    {
        typedef typename _I::Next Next;
        return std::get<_I::i+1>(functions).push(_fnc(v), functions, Next());
    }

    template<typename _F, typename _I>
    void finish(_F& functions, _I)
    {
        typedef typename _I::Next Next;
        std::get<_I::i>(functions).finish(functions, Next());
    }

};

template<typename _Fnc>
struct _Map<_Fnc, typename std::enable_if<std::is_member_function_pointer<_Fnc>::value>::type>
{
    static const StepType stepType = StepType::eTransformator;
    _Fnc _fnc;
    _Map(_Fnc&& fnc)
    : _fnc(fnc)
    {
    }

    template<typename _T, typename _F, typename _I>
    bool push(_T&& v, _F& functions, _I i)
    {
        typedef typename _I::Next Next;
        return std::get<_I::i+1>(functions).push((v.*_fnc)(), functions, Next());
    }

    template<typename _F, typename _I>
    void finish(_F& functions, _I)
    {
        typedef typename _I::Next Next;
        std::get<_I::i>(functions).finish(functions, Next());
    }

};

template<typename _Fnc>
struct _Map<_Fnc, typename std::enable_if<std::is_member_object_pointer<_Fnc>::value>::type>
{
    static const StepType stepType = StepType::eTransformator;
    _Fnc _fnc;
    _Map(_Fnc&& fnc)
    : _fnc(fnc)
    {
    }

    template<typename _T, typename _F, typename _I>
    bool push(_T&& v, _F& functions, _I i)
    {
        typedef typename _I::Next Next;
        return std::get<_I::i+1>(functions).push((v.*_fnc), functions, Next());
    }

    template<typename _F, typename _I>
    void finish(_F& functions, _I)
    {
        typedef typename _I::Next Next;
        std::get<_I::i>(functions).finish(functions, Next());
    }

};

template<typename _Fnc>
_Map<_Fnc> map(_Fnc&& fnc)
{
    return _Map<_Fnc>(std::move(fnc));
}

template<typename _Fnc>
struct _ForEach
{
    static const StepType stepType = StepType::eTerminator;
    _Fnc _fnc;
    _ForEach(_Fnc&& fnc)
    : _fnc(fnc)
    {
    }

    template<typename _T, typename _F, typename _I>
    bool push(_T&& v, _F& functions, _I)
    {
        _fnc(std::move(v));
        return true;
    }

    template<typename _F, typename _I>
    void finish(_F& functions, _I)
    {
    }

};

template<typename _Fnc>
_ForEach<_Fnc> foreach(_Fnc&& fnc)
{
    return _ForEach<_Fnc>(std::move(fnc));
}

template<typename _Fnc>
struct _Filter
{
    static const StepType stepType = StepType::eFilter;
    _Fnc _fnc;
    _Filter(_Fnc&& fnc)
    : _fnc(fnc)
    {
    }

    template<typename _T, typename _F, typename _I>
    bool push(_T&& v, _F& functions, _I)
    {
        if(_fnc(v))
        {
            typedef typename _I::Next Next;
            return std::get<_I::i+1>(functions).push(std::move(v), functions, Next());
        }

        return true;
    }

    template<typename _F, typename _I>
    void finish(_F& functions, _I)
    {
        typedef typename _I::Next Next;
        std::get<_I::i>(functions).finish(functions, Next());
    }
};

template<typename _Fnc>
_Filter<_Fnc> filter(_Fnc&& fnc)
{
    return _Filter<_Fnc>(std::move(fnc));
}

template<typename _Pred>
struct _TakeWhile
{
    static const StepType stepType = StepType::eLimiter;
    _Pred _pred;

    _TakeWhile(_Pred&& pred)
    : _pred(pred)
    {
    }

    template<typename _T, typename _F, typename _I>
    bool push(_T&& v, _F& functions, _I)
    {
        if(_pred(v))
        {
            typedef typename _I::Next Next;
            return std::get<_I::i+1>(functions).push(std::move(v), functions, Next());
        }
        return false;
    }

    template<typename _F, typename _I>
    void finish(_F& functions, _I)
    {
    }
};

template<typename _Pred>
_TakeWhile<_Pred> takewhile(_Pred&& pred)
{
    return _TakeWhile<_Pred>(std::move(pred));
}

struct _Take
{
    static const StepType stepType = StepType::eLimiter;
    int _count;

    _Take(int count)
    : _count(count)
    {
    }

    template<typename _T, typename _F, typename _I>
    bool push(_T&& v, _F& functions, _I)
    {
        if(_count-- != 0)
        {
            typedef typename _I::Next Next;
            return std::get<_I::i+1>(functions).push(std::move(v), functions, Next());
        }
        return false;
    }

    template<typename _F, typename _I>
    void finish(_F& functions, _I)
    {
    }
};

_Take take(int count)
{
    return _Take(count);
}

struct _Drop
{
    static const StepType stepType = StepType::eLimiter;
    int _count;

    _Drop(int count)
    : _count(count)
    {
    }

    template<typename _T, typename _F, typename _I>
    bool push(_T&& v, _F& functions, _I)
    {
        if(_count != 0)
        {
            --_count;
            return true;
        }
        typedef typename _I::Next Next;
        return std::get<_I::i+1>(functions).push(std::move(v), functions, Next());
    }

    template<typename _F, typename _I>
    void finish(_F& functions, _I)
    {
    }
};

_Drop drop(int count)
{
    return _Drop(count);
}

template<typename _ResultType, typename _Fnc>
struct _Reduce
{
    static const StepType stepType = StepType::eReducer;

    typedef _ResultType ResultType;
    ResultType _result;
    _Fnc _fnc;

    _Reduce(_ResultType initialValue, _Fnc fnc)
    : _result(initialValue)
    , _fnc(fnc)
    {
    }

    template<typename _T, typename _F, typename _I>
    bool push(_T&& v, _F& functions, _I)
    {
        //typedef typename _I::Next Next;
        _result = _fnc(_result, v);
        return true;
    }

    template<typename _F, typename _I>
    void finish(_F& functions, _I)
    {
    }

    ResultType get()
    {
        return std::move(_result);
    }
};

template<typename _ResultType, typename _Fnc>
_Reduce<_ResultType, _Fnc> reduce(_ResultType initialValue, _Fnc fnc)
{
    return _Reduce<_ResultType, _Fnc>(initialValue, fnc);
}

//
template<typename _ResultType>
struct _ToVector
{
    static const StepType stepType = StepType::eReducer;

    typedef _ResultType ResultType;
    ResultType _result;

    _ToVector()
    {
    }

    _ToVector(size_t sz)
    {
      _result.reserve(sz);
    }

    template<typename _T, typename _F, typename _I>
    bool push(_T&& v, _F& functions, _I)
    {
        //typedef typename _I::Next Next;
        _result.emplace_back(std::move(v));
        return true;
    }

    template<typename _F, typename _I>
    void finish(_F& functions, _I)
    {
    }

    ResultType get()
    {
        return std::move(_result);
    }
};

template<typename _ResultType>
_ToVector<_ResultType> tovector()
{
    return _ToVector<_ResultType>();
}

template<typename _ResultType>
_ToVector<_ResultType> tovector(size_t sz)
{
    return _ToVector<_ResultType>(sz);
}

template<typename _Fnc>
struct _AllOf
{
    static const StepType stepType = StepType::eReducer;
    _Fnc _fnc;
    typedef bool ResultType;
    ResultType _result;
    _AllOf(_Fnc&& fnc)
    : _fnc(fnc)
    , _result(true)
    {
    }

    template<typename _T, typename _F, typename _I>
    bool push(_T&& v, _F& functions, _I)
    {
        _result = _fnc(v);
        return _result;
    }

    template<typename _F, typename _I>
    void finish(_F& functions, _I)
    {
    }

    ResultType get()
    {
        return _result;
    }

};

template<typename _Fnc>
_AllOf<_Fnc> allof(_Fnc&& fnc)
{
    return _AllOf<_Fnc>(std::move(fnc));
}

template<typename _Fnc>
struct _AnyOf
{
    static const StepType stepType = StepType::eReducer;
    _Fnc _fnc;
    typedef bool ResultType;
    ResultType _result;
    _AnyOf(_Fnc&& fnc)
    : _fnc(fnc)
    , _result(true)
    {
    }

    template<typename _T, typename _F, typename _I>
    bool push(_T&& v, _F& functions, _I)
    {
        _result = _fnc(v);
        return !_result;
    }

    template<typename _F, typename _I>
    void finish(_F& functions, _I)
    {
    }

    ResultType get()
    {
        return _result;
    }

};

template<typename _Fnc>
_AnyOf<_Fnc> anyof(_Fnc&& fnc)
{
    return _AnyOf<_Fnc>(std::move(fnc));
}

template<typename _Fnc>
struct _NoneOf
{
    static const StepType stepType = StepType::eReducer;
    _Fnc _fnc;
    typedef bool ResultType;
    ResultType _result;
    _NoneOf(_Fnc&& fnc)
    : _fnc(fnc)
    , _result(true)
    {
    }

    template<typename _T, typename _F, typename _I>
    bool push(_T&& v, _F& functions, _I)
    {
        _result = !_fnc(v);
        return _result;
    }

    template<typename _F, typename _I>
    void finish(_F& functions, _I)
    {
    }

    ResultType get()
    {
        return _result;
    }

};

template<typename _Fnc>
_NoneOf<_Fnc> noneof(_Fnc&& fnc)
{
    return _NoneOf<_Fnc>(std::move(fnc));
}
#endif /* _FUNCTIONS_H_ */
