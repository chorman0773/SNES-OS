#ifdef __cplusplus
#ifndef __Dynamic_hpp_2018_06_07_13_14
#define __Dynamic_hpp_2018_06_07_13_14

#pragma macros import("__cpp_qualified_typename",type) define("__cppqualified_typename",type)

#include <functional>
#include <string>

using std::function;
using std::string;

template<typename T> struct mangled_name{
static const inline string name = __cpp_qualified_typename(T);
};

template<typename Ret,typename... Args> Ret(*)(Args...) linkCppFunction(string funcName){
  
}

#endif
#endif
