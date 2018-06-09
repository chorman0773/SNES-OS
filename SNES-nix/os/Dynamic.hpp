#ifdef __cplusplus
#ifndef __Dynamic_hpp_2018_06_07_13_14
#define __Dynamic_hpp_2018_06_07_13_14

#pragma macros import("__cpp_qualified_typename",type) define("__cpp_qualified_typename",type)
#pragma macros import("__cpp_typename",type) define("__cpp_typename",type)
#pragma macros import("__cpp_from_qualified",typename) define("__cpp_from_qualified",typename)
#pragma macros import("__cpp_to_qualified",typename) define("__cpp_to_qualified",typename)
#pragma macros import("__cpp_qualified_classname",cl) define("__cpp_qualified_classname",cl)
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
                                                                                     
template<typename Base> class DynamicClass;

class DynamicLibrary{
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
  template<typename Base> vector<DynamicClass<Base>> getAllExtending(){
    vector<DynamicClass<Base>> ret;
    
    return ret;
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
  DynamicFunction()=default;
  DynamicFunction(const string& name,DynamicLibrary* lib):lib(lib){
    sym = lib->lookup(name+"@"+descriptor+"#");
    lib->checkType<Ret(Args...)>(sym);
  }
  template<typename... Varargs> Ret&& operator()(Args... args,Varargs... vaargs)noexcept{
    Ret(*ptr)(Args...)noexcept = (Ret(*)(Args...)noexcept)lib->link(sym);
    return ptr(std::forward_if_noexcept<Args>(args)...,std::forward_if_noexcept<Varargs>(vaargs)...);
  }
};

template<typename Type> class DynamicField{
private:
  symbol* sym = nullptr;
  DynamicLibrary* lib = nullptr;
public:
  DynamicField()=default;
  DynamicField(const string& name,DynamicLibrary* lib):lib(lib){
   sym = lib->lookup(name); 
   lib->checkType<Type>(sym);
  }
  Type* operator&(){
   return (Type*)lib->link(sym); 
  }
  operator Type&(){
   return *((Type*)lib->link(sym));
  }
  operator const Type&()const{
    return *((Type*)lib->link(sym));
  }
  Type& get(){
   return *((Type*)lib->link(sym)); 
  }
  const Type& get()const{
   return *((const Type*)lib->link(sym));
  }
  const Type* operator&()const{
   return (const Type*)lib->link(sym);
  }
  template<typename T,typename Ret=decltype(declval<Type&>()=declval<T>())> Ret operator=(T&& t){
   return  get()=t;
  }
  template<typename T,typename Ret=decltype(declval<Type&>()+declval<T>())> Ret operator+(T&& t){
   return get()+t; 
  }
  template<typename T,typename Ret=decltype(declval<const Type&>()+declval<T>())> Ret operator+(T&& t)const{
   return get()+t; 
  }
  template<typename T,typename Ret=decltype(declval<Type&>()+=declval<T>())> Ret operator+=(T&& t){
   return get()+=t; 
  }
  template<typename T,typename Ret=decltype(declval<Type&>()-declval<T>())> Ret operator-(T&& t){
   return get()-t; 
  }
  template<typename T,typename Ret=decltype(declval<const Type&>()-declval<T>())> Ret operator-(T&& t)const{
   return get()-t; 
  }
  template<typename T,typename Ret=decltype(declval<Type&>()-=declval<T>())> Ret operator-=(T&& t){
   return get()-=t; 
  }
  template<typename T,typename Ret=decltype(declval<Type&>()*declval<T>())> Ret operator*(T&& t){
   return get()*t; 
  }
  template<typename T,typename Ret=decltype(declval<const Type&>()*declval<T>())> Ret operator*(T&& t)const{
   return get()*t; 
  }
  template<typename T,typename Ret=decltype(declval<Type&>()*=declval<T>())> Ret operator*=(T&& t){
   return get()*=t; 
  }
  template<typename T,typename Ret=decltype(declval<Type&>()/declval<T>())> Ret operator/(T&& t){
   return get()-t; 
  }
  template<typename T,typename Ret=decltype(declval<const Type&>()/declval<T>())> Ret operator/(T&& t)const{
   return get()-t; 
  }
  template<typename T,typename=decltype(T(declval<T&>()))> operator T(){
   return (T)get(); 
  }
  template<typename T,typename=decltype(T(declval<const T&>()))> operator T()const{
   return (T)get(); 
  }
};
                                                                                     

template<class Base,typename=typename std::enable_if<std::is_polymorphic<Base>::value>::type> class DynamicClass{
  const string& name;
  symbol* sym;
  DynamicLibrary* lib;
  size_t size;
  /*
    Use void* for type erasure
  */
  template<typename... Args> Base& constructTo(void* b,Args&&... args)const{
    string ctorName = name+"::{ctor}"s;
    string ctorSymbol = ctorName+"@*L"s+name+";"s+(string(mangled_symbol_name<Args>) + ...);
    void(*ctor)(void*,Args...) = (void(*)(void*,Args...))lib->link(lib->lookup(ctorSymbol);
    if(ctor==nullptr)
         throw bad_type_exception<void(Args&&...)>("unknown");
    ctor(b,std::forward<Args>(args)...);
    return *(Base*)b;
  }
  void destroyAt(void* b)const{
   string dtorName  = name+"::{dtor}@*L"s+name+";#"s;
   void(*dtor)(void*) = (void(*)(void*))lib->link(lib->lookup(dtorName));
  }
public:
  DynamicClass()=default;
  DynamicClass(const string& name,DynamicLibrary* lib):lib(lib),name(name){
    sym = lib->lookup(name);
    size = *((size_t*)(((char*)lib->link(sym))+6);
  }
  template<typename... Args> Base* construct(Args&&... args)const{
    void* constructed = ::operator new(size);
    return &constructTo(constructed,args...);
  }
  void destroy(Base* b){
   destroyAt(b);
  }
  template<typename... Args> Base* operator()(Args&&... args)const{
   return construct(args...); 
  }
};

#endif
#endif
