#ifndef __Objects_hpp_2018_05_22_16_22
#define __Objects_hpp_2018_05_22_16_22
#include "References.hpp"
namespace java{
  class Class;
  namespace Objects{
    ReferencePtr newInstance(const Class&);
    bool instanceof(const ReferencePtr&,const Class&);
    void referenceClone(ReferencePtr&,const ReferencePtr&);
    const ReferencePtr& getClassObject(const Class&);
  };
};
#endif
