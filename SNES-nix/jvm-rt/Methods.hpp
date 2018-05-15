#ifndef __Methods_hpp_2018_05_14_17_23
#define __Methods_hpp_2018_05_14_17_23
#include <string>

#include "Invocation.hpp"
#include "Types.hpp"

using std::string;
namespace java{
  class Class;
  class MethodRef;
  class MethodHandle{
  private:
    const Class& cl;
    const MethodRef& ref;
  public:
    MethodHandle(const Class&,const MethodRef&);
    MethodHandle(const string&);
    MethodHandle(const string&,const string&,const initializer_list<TypeDescriptor>&,const TypeDescriptor&);
    Invocation invokespecial(const Invocation&);
    Invocation invokevirtual(const Invocation&);
    Invocation invokedynamic(const Invocation&);
    Invocation invokestatic(const Invocation&);
    Invocation invokeinterface(const Invocation&);
    bool checkInvokeSpecial(const Invocation&);
    bool checkInvokeVirtual(const Invocation&);
    bool checkInvokeDynamic(const Invocation&);
    bool checkInvokeStatic(const Invocation&);
    bool checkInvokeInterface(const Invocation&);
    bool checkValid();
  };
  
  class FieldHandle{
  private:
    const Class& cl;
    const FieldRef& ref;
  public:
    FieldHandle(const Class&,const FieldRef&);
    FieldHandle(const string&);
    FieldHandle(const string&,const string&,const TypeDescriptor&);
    void getfield(Invocation&);
    void getstatic(Invocation&);
    bool checkGetField(const Invocation&);
    bool checkGetStatic(const Invocation&);
    bool checkValid();
  };

};

#endif
