#ifndef __Objects_hpp_2018_05_22_16_22
#define __Objects_hpp_2018_05_22_16_22
#include "References.hpp"
#include "Types.hpp"
#include <string>
using std::string;
namespace java{
  class Class;
  class ReferenceType;
  namespace Objects{
    ReferencePtr newInstance(const Class&);
    bool instanceof(const ReferencePtr&,const Class&);
    void referenceClone(ReferencePtr&,const ReferencePtr&);
    const ReferencePtr& getClassObject(const Class&);
    size_t getAllocationSize(const Class&);
  };
  namespace Strings{
    ReferencePtr fromUtf8(const char*);
    ReferencePtr fromUtf8STL(const string&)
    ReferencePtr fromUtf16(const u16char_t*);
    ReferencePtr fromUtf16STL(const u16string&);
  };
  namespace Arrays{
    ReferencePtr anewArray(const Class&,int);
    ReferencePtr newArray(Primitive,int);
    ReferencePtr multianewArray(Primitive,int,int[]);
    ReferencePtr multianewArray(const Class&,int,int[]);
    int getByte(ReferencePtr,int);
    void storeByte(ReferencePtr,int,int);
    bool getBoolean(ReferencePtr,int);
    void storeBoolean(ReferencePtr,int,bool);
    int getShort(ReferencePtr,int);
    void storeShort(ReferencePtr,int,int);
    int getInt(ReferencePtr,int);
    void storeInt(ReferencePtr,int,int);
    long long getLong(ReferencePtr,int);
    void storeLong(ReferencePtr,int,long long);
    ReferencePtr getReference(ReferencePtr,int);
    void storeReference(ReferencePtr,int,ReferencePtr);
    bool checkStoreReference(ReferencePtr,ReferencePtr);
    int getLength(ReferencePtr);
    size_t getAllocationSize(Primitive,int);
    size_t getReferenceAllocationSize(int);
  };
};
#endif
