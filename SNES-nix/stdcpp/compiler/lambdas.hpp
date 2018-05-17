#ifndef __lambdas_hpp_2018_05_16_19_20
#define __lambdas_hpp_2018_05_16_19_20

#include <utility>

template<size_t I> struct lambda_template_parameter{
  constexpr static size_t index = I;
};

struct lambda_Tnoexcept{};

struct lambda_Tconstexpr;



template<template ConstexprTag,template TemplateDescriptor,typename NoExceptTag,typename ReturnType,typename CapturesDescriptor,typename... ArgsType> struct lambda_Texpression;

template<typename ReturnType,typename... ArgsType> lambda_expression<void,void,void,ReturnType,void,ArgsType...> struct lambda_Texpression{
  using FunctionType = ReturnType(ArgsType...);
  FunctionType& targetFunctionRef;
public:
  ReturnType(FunctionType& targetRef):targetFunctionRef(targetRef){}
  operator FunctionType*(){
    return &targetFunctionRef;
  }
  ReturnType operator()(ArgsType... args){
    return targetFunctionRef(std::forward(args)...);
  }
};

template<typename ReturnType,typename... ArgsType> struct lambda_Texpression<void,void,lambda_Tnoexcept,ReturnType,void,ArgsType...>{
  using FunctionType = ReturnType(ArgsType...)noexcept;
  FunctionType& targetFunctionRef;
public:
  lambda_Texpression(FunctionType& targetRef):targetFunctionRef(targetRef){}
  operator FunctionType*(){
    return &targetFunctionRef;
  }
  ReturnType operator()(ArgsType... args)noexcept{
    return targetFunctionRef(std::forward(args)...);
  }
};

template<typename ReturnType,typename... ArgsType> lambda_expression<lambda_Tconstexpr,void,void,ReturnType,void,ArgsType...> struct lambda_Texpression{
  using FunctionType = constexpr ReturnType(ArgsType...);
  FunctionType& targetFunctionRef;
public:
  ReturnType(FunctionType& targetRef):targetFunctionRef(targetRef){}
  operator FunctionType*(){
    return &targetFunctionRef;
  }
  constexpr ReturnType operator()(ArgsType... args){
    return targetFunctionRef(std::forward(args)...);
  }
};

template<typename ReturnType,typename... ArgsType> struct lambda_Texpression<lambda_Tconstexpr,void,lambda_Tnoexcept,ReturnType,void,ArgsType...>{
  using FunctionType = constexpr ReturnType(ArgsType...)noexcept;
  FunctionType& targetFunctionRef;
public:
  lambda_Texpression(FunctionType& targetRef):targetFunctionRef(targetRef){}
  operator FunctionType*(){
    return &targetFunctionRef;
  }
  constexpr ReturnType operator()(ArgsType... args)noexcept{
    return targetFunctionRef(std::forward(args)...);
  }
};


template<typename ReturnType,typename Captures,typename... ArgsTypes> struct lambda_Texpression<void,void,void,ReturnType,Captures,ArgsType...>{
  using FunctionType = ReturnType(Captures,ArgsType...);
  FunctionType& targetFunctionRef;
  Captures& captures;
public:
  lambda_Texpression(Captures& c,FunctionType& targetRef):c(captures),targetFunctionRef(targetRef){}
  ReturnType operator()(ArgsType... args){
   return targetFunctionRef(captures,std::forward(args)...); 
  }
};


template<typename ReturnType,typename Captures,typename... ArgsTypes> struct lambda_Texpression<void,void,lambda_Tnoexcept,ReturnType,Captures,ArgsType...>{
  using FunctionType = ReturnType(Captures&,ArgsType...)noexcept;
  FunctionType& targetFunctionRef;
  Captures& captures;
public:
  lambda_Texpression(Captures& c,FunctionType& targetRef):c(captures),targetFunctionRef(targetRef){}
  ReturnType operator()(ArgsType... args)noexcept{
   return targetFunctionRef(captures,std::forward(args)...); 
  }
};



#endif
