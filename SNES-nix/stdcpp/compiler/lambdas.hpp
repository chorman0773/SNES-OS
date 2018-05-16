#ifndef __lambdas_hpp_2018_05_16_19_20
#define __lambdas_hpp_2018_05_16_19_20

#include <utility>
#include <tuple>

template<size_t I> struct lambda_template_parameter{
  constexpr static size_t index = I;
};

struct lambda_Tnoexcept{};



template<template TemplateDescriptor,typename NoExceptTag,typename ReturnType,typename CapturesDescriptor,typename... ArgsType> struct lambda_Texpression;

template<typename ReturnType,typename... ArgsType> lambda_expression<void,void,ReturnType,void,ArgsType...> struct lambda_Texpression{
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

template<typename ReturnType,typename... ArgsType> lambda_expression<void,lambda_Tnoexcept,ReturnType,void,ArgsType...> struct lambda_Texpression{
  using FunctionType = ReturnType(ArgsType...)noexcept;
  FunctionType& targetFunctionRef;
public:
  ReturnType(FunctionType& targetRef):targetFunctionRef(targetRef){}
  operator FunctionType*(){
    return &targetFunctionRef;
  }
  ReturnType operator()(ArgsType... args)noexcept{
    return targetFunctionRef(std::forward(args)...);
  }
};




#endif
