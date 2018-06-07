#ifdef __cplusplus
#ifndef __Dynamic_hpp_2018_06_07_13_14
#define __Dynamic_hpp_2018_06_07_13_14

#pragma macros import("__cpp_qualified_typename",type) define("__cpp_qualified_typename",type)
#pragma macros import("__cpp_typename",type) define("__cpp_typename",type)
#pragma macros import("__cpp_from_qualified",typename) define("__cpp_from_qualified",typename)
#pragma macros import("__cpp_to_qualified",typename) define("__cpp_to_qualified",typename)
#include <cstdio>
#include <functional>
#include <string>
#include <stdexcept>
#include <os/ExecutibleLaunch.h>
#include <gcc/exec/metadata.h>


using std::function;
using std::string;



template<typename T> constexpr const char mangled_symbol_name[] = __cpp_qualified_name(T);

class illegal_type_exception final:public exception{
private:
  string expectedType;
  string actualType;
public:
  template<typename T> illegal_type_exception(const string& actualType):expectedType(__cpp_from_qualified(__cpp_qualified_name(T)),
            actualType(actualType){}
    const char* what()override noexcept{
      return ("Type Error: Expected "s+expectedType+" got "s+actualType).c_str();
    }
};

class DynamicLibrary{
private:
  ExecutibleHeader* header;
  FILE* executible;
public:
  void* link(symbol*);
  symbol* lookup(const string&);
  template<typename T> void checkType(symbol* sym){
    string inputType = __cpp_qualified_typename(T);
    MD_DeclType* md_decltype = (MD_DeclType*)getSymbolMetadata(sym,"DeclType");
    string unqualifiedType = md_decltype->type;
    string type = typenames::toQualified(md_decltype->type);
    if(type!=inputType)
      throw illegal_type_exception<T>(unqualifiedType);
  }
};

template<typename Type> class DynamicFunction;
template<typename Ret,typename... Args> class DynamicFunction<Ret(Args...)>{
private:
  static inline const string descriptor = (string(mangled_symbol_name) + ...);
  symbol* sym = nullptr;
  DynamicLibrary* lib = nullptr;
public:
  DynamicFunction(){}
  DynamicFunction(const string& name,DynamicLibrary* lib):lib(lib){
    sym = lib->lookup(name+"@"+descriptor);
    lib->checkType<Ret(Args...)>(sym);
  }
  Ret&& operator()(Args... args){
    Ret(*ptr)(Args...) = (Ret(*)(Args...))lib->link(sym);
    return std::forward<Ret>(ptr(std::forward<Args>(args)...));
  }
};


template<typename Ret,typename... Args> class DynamicFunction<Ret(Args...)noexcept>{
  private:
  static inline const string descriptor = (string(mangled_symbol_name) + ...)+"#";
  symbol* sym = nullptr;
  DynamicLibrary* lib = nullptr;
public:
  DynamicFunction(){}
  DynamicFunction(const string& name,DynamicLibrary* lib):lib(lib){
    sym = lib->lookup(name+"@"+descriptor);
    lib->checkType<Ret(Args...)>(sym);
  }
  Ret&& operator()(Args... args)noexcept{
    Ret(*ptr)(Args...)noexcept = (Ret(*)(Args...)noexcept)lib->link(sym);
    return ptr(std::forward_if_noexcept<Args>(args)...);
  }
};
                                                                                     
template<typename Ret,typename... Args> class DynamicFunction<Ret(Args...,...)>{
private:
  static inline const string descriptor = (string(mangled_symbol_name) + ...)+"..."s;
  symbol* sym = nullptr;
  DynamicLibrary* lib = nullptr;
public:
  DynamicFunction(){}
  DynamicFunction(const string& name,DynamicLibrary* lib):lib(lib){
    sym = lib->lookup(name+"@"+descriptor);
    lib->checkType<Ret(Args...)>(sym);
  }
  template<typename... Varargs> Ret&& operator()(Args... args,Varargs... vaargs){
    Ret(*ptr)(Args...) = (Ret(*)(Args...))lib->link(sym);
    return ptr(std::forward<Args>(args)...,std::forward<Varargs>(vaargs)...);
  }
};


template<typename Ret,typename... Args> class DynamicFunction<Ret(Args...,...)noexcept>{
  private:
  static inline const string descriptor = (string(mangled_symbol_name) + ...)+"...#"s;
  symbol* sym = nullptr;
  DynamicLibrary* lib = nullptr;
public:
  DynamicFunction(){}
  DynamicFunction(const string& name,DynamicLibrary* lib):lib(lib){
    sym = lib->lookup(name+"@"+descriptor+"#");
    lib->checkType<Ret(Args...)>(sym);
  }
  template<typename... Varargs> Ret&& operator()(Args... args,Varargs... vaargs)noexcept{
    Ret(*ptr)(Args...)noexcept = (Ret(*)(Args...)noexcept)lib->link(sym);
    return ptr(std::forward_if_noexcept<Args>(args)...,std::forward_if_noexcept<Varargs>(vaargs)...);
  }
};


template<typename Base> class DynamicClass{
  symbol* sym;
  DynamicLibrary* library;
  symbol* dtor;
public:
  DynamicClass(){
    
  }
};

#endif
#endif
