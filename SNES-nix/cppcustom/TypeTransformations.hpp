#ifndef __TypeTransformations_hpp_2018_05_29_14_06
#define __TypeTransformations_hpp_2018_05_29_14_06

#include <type_traits>
#include <cppcustom/type_traits>

#pragma macros import("__somewhere",expn) define("__somewhere",expn)
#pragma macros import("__nowhere",expn) define("__nowhere",expn)
#pragma macros import("__everywhere",expn) define("__everywhere",expn)

namespace detail{
  template<typename T> struct echo_type{
    using type = T;
  };
  template<template<typename... > typename base,typename T,size_t N,typename... rest> struct repeat_types_helper:repeat_types_helper<base,T,N-1,T,rest...>{};
  template<template<typename... > typename base,typename T,typename... rest> struct repeat_types_helper<base,T,0,rest>:echo_type<base<rest>>{};
};

template<template<typename... >typename base,typename T,size_t N> using repeat_types = detail::repeat_types_helper<base,T,N>;

template<typename target,typename T> struct in_varargs_list;

template<template<typename... >typename base,typename T> struct in_varargs_list<base<__nowhere(T)>,T>:std::false_type{};
template<template<typename... >typename base,typename T> struct in_varargs_list<base<__somewhere(T)>,T>:std::true_type{};




#endif
