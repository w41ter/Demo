#include <type_traits>
#include <tuple>
#include <utility>
 
namespace simple {
 
/*
    Placeholder
*/
 
template <int N>
struct placeholder {};
 
const placeholder<1> _1; const placeholder<6>  _6;  const placeholder<11> _11; const placeholder<16> _16;
const placeholder<2> _2; const placeholder<7>  _7;  const placeholder<12> _12; const placeholder<17> _17;
const placeholder<3> _3; const placeholder<8>  _8;  const placeholder<13> _13; const placeholder<18> _18;
const placeholder<4> _4; const placeholder<9>  _9;  const placeholder<14> _14; const placeholder<19> _19;
const placeholder<5> _5; const placeholder<10> _10; const placeholder<15> _15; const placeholder<20> _20;
 
/*
    Sequence & Generater
*/
 
template <int... N>
struct seq { typedef seq<N..., sizeof...(N)> next_type; };
 
template <typename... P>
struct gen;
 
template <>
struct gen<>
{
    typedef seq<> seq_type;
};
 
template <typename P1, typename... P>
struct gen<P1, P...>
{
    typedef typename gen<P...>::seq_type::next_type seq_type;
};
 
/*
    Merge the type of tuple
*/
 
template <typename T, typename TupleT>
struct tuple_insert;
 
template <typename T, typename... TypesT>
struct tuple_insert<T, std::tuple<TypesT...>>
{
    typedef std::tuple<T, TypesT...> type;
};
 
template <class TupleT, typename... BindT>
struct merge;
 
template <typename... ParsT>
struct merge<std::tuple<ParsT...>>
{
    typedef std::tuple<> type;
};
 
template <typename... ParsT, typename B1, typename... BindT>
struct merge<std::tuple<ParsT...>, B1, BindT...>
{
    typedef std::tuple<ParsT...> tp_t;
    typedef typename tuple_insert<
            B1, 
            typename merge<tp_t, BindT...>::type
    >::type type;
};
 
template <typename... ParsT, int N, typename... BindT>
struct merge<std::tuple<ParsT...>, const placeholder<N>&, BindT...>
{
    typedef std::tuple<ParsT...> tp_t;
    typedef typename tuple_insert<
            typename std::tuple_element<N - 1, tp_t>::type,
            typename merge<tp_t, BindT...>::type
    >::type type;
};
 
/*
    Select the value of tuple
*/
 
template <typename T, class TupleT>
inline auto select(TupleT& /*tp*/, T&& val) -> T&&
{
    return std::forward<T>(val);
}
 
template <int N, class TupleT>
inline auto select(TupleT& tp, placeholder<N>) -> decltype(std::get<N - 1>(tp))
{
    return std::get<N - 1>(tp);
}
 
/*
    Return type traits
*/
 
template <typename F>
struct return_traits : return_traits<decltype(&F::operator())> {};
 
template <typename T>
struct return_traits<T*> : return_traits<T> {};
 
// check function
 
template <typename R, typename... P>
struct return_traits<R(*)(P...)> { typedef R type; };
 
// check member function
 
#define RESULT_TRAITS__(...) \
    template <typename R, typename C, typename... P> \
    struct return_traits<R(C::*)(P...) __VA_ARGS__> { typedef R type; };
 
RESULT_TRAITS__()
RESULT_TRAITS__(const)
RESULT_TRAITS__(volatile)
RESULT_TRAITS__(const volatile)
 
#undef RESULT_TRAITS__
 
/*
    Type detect
*/
 
template <typename T>
struct is_pointer_noref
    : std::is_pointer<typename std::remove_reference<T>::type>
{};
 
template <typename T>
struct is_memfunc_noref
    : std::is_member_function_pointer<typename std::remove_reference<T>::type>
{};
 
template <typename T>
struct is_wrapper
    : std::false_type
{};
 
template <typename T>
struct is_wrapper<std::reference_wrapper<T>>
    : std::true_type
{};
 
template <typename T>
struct is_wrapper_noref
    : is_wrapper<typename std::remove_reference<typename std::remove_cv<T>::type>::type>
{};
 
/*
    The invoker for call a callable
*/
 
template <typename R, typename F, typename... P>
inline typename std::enable_if<is_pointer_noref<F>::value,
R>::type invoke(F&& f, P&&... args)
{
    return (*std::forward<F>(f))(std::forward<P>(args)...);
}
 
template <typename R, typename F, typename P1, typename... P>
inline typename std::enable_if<is_memfunc_noref<F>::value &&
                               is_pointer_noref<P1>::value,
R>::type invoke(F&& f, P1&& this_ptr, P&&... args)
{
    return (std::forward<P1>(this_ptr)->*std::forward<F>(f))(std::forward<P>(args)...);
}
 
template <typename R, typename F, typename P1, typename... P>
inline typename std::enable_if<is_memfunc_noref<F>::value &&
                              !is_pointer_noref<P1>::value && !is_wrapper_noref<P1>::value,
R>::type invoke(F&& f, P1&& this_obj, P&&... args)
{
    return (std::forward<P1>(this_obj).*std::forward<F>(f))(std::forward<P>(args)...);
}
 
template <typename R, typename F, typename P1, typename... P>
inline typename std::enable_if<is_memfunc_noref<F>::value &&
                              !is_pointer_noref<P1>::value && is_wrapper_noref<P1>::value,
R>::type invoke(F&& f, P1&& this_wrp, P&&... args)
{
    typedef typename std::remove_reference<P1>::type wrapper_t;
    typedef typename wrapper_t::type this_t;
    return (static_cast<this_t&>(std::forward<P1>(this_wrp)).*std::forward<F>(f))(std::forward<P>(args)...);
}
 
template <typename R, typename F, typename... P>
inline typename std::enable_if<!is_pointer_noref<F>::value && !is_memfunc_noref<F>::value,
R>::type invoke(F&& f, P&&... args)
{
    return std::forward<F>(f)(std::forward<P>(args)...);
}
 
/*
    Simple functor for bind callable type and arguments
*/
 
template<typename FuncT, typename... ParsT>
class fr
{
    typedef std::tuple<typename std::decay<ParsT>::type...> args_type;
    typedef typename std::decay<FuncT>::type                callable_type;
    typedef typename return_traits<callable_type>::type     return_type;
 
    callable_type call_;
    args_type     args_;
 
    template <class TupleT, int... N>
    return_type do_call(TupleT&& tp, seq<N...>)
    {
        typedef typename merge<TupleT, ParsT...>::type params_t;
        return invoke<return_type>
            (call_, static_cast<typename std::tuple_element<N, params_t>::type>(select(tp, std::get<N>(args_)))...);
    }
 
public:
#if defined(_MSC_VER) && (_MSC_VER <= 1800)
    /*
        <MSVC 2013> Visual Studio does not support defaulted move constructors or 
                    move-assignment operators as the C++11 standard mandates.
        See: http://stackoverflow.com/questions/24573963/move-constructor-invalid-type-for-defaulted-constructor-vs-2013
    */
    fr(fr&& rhs) : call_(std::move(rhs.call_)), args_(std::move(rhs.args_)) {}
#else
    fr(fr&&)      = default;
#endif
    fr(const fr&) = default;
 
    fr(FuncT f, ParsT... args)
        : call_(std::forward<FuncT>(f))
        , args_(std::forward<ParsT>(args)...)
    {}
 
    template <typename... P>
    return_type operator()(P&&... args)
    {
        return do_call(std::forward_as_tuple(std::forward<P>(args)...), typename gen<ParsT...>::seq_type());
    }
};
 
/*
    Bind function arguments
*/
 
template <typename F, typename... P>
inline fr<F&&, P&&...> bind(F&& f, P&&... args)
{
    return { std::forward<F>(f), std::forward<P>(args)... };
}
 
} // namespace simple