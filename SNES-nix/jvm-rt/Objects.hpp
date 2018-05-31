#ifndef __Objects_hpp_2018_05_22_16_22
#define __Objects_hpp_2018_05_22_16_22
#include "References.hpp"
#include <string>
using std::string;
namespace java{
  class Class;
  namespace Objects{
    ReferencePtr newInstance(const Class&);
    bool instanceof(const ReferencePtr&,const Class&);
    void referenceClone(ReferencePtr&,const ReferencePtr&);
    const ReferencePtr& getClassObject(const Class&);
  };
  namespace Strings{
    ReferencePtr fromUtf8(const char*);
    ReferencePtr fromUtf8STL(const string&)
    ReferencePtr fromUtf16(const u16char_t*);
    ReferencePtr fromUtf16STL(const u16string&);
  };
};
#endif
