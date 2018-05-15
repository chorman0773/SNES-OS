#include "jni/jni.h"
#include "References.hpp"
#include "Invocation.hpp"
#include "Methods.hpp"
#include "Objects.hpp"
#include "Threads.hpp"
#include "Helpers.hpp"

namespace java{
  struct lang{
    struct Object{
      static void ctor__V(Thread& t,Invocation& i){}
      static jint hashCode_I(Thread& t,Invocation& i){
        ReferencePtr ref = i.getReference(0);
        return static_cast<jint>(ref->getHandle());
      }
      static jclass getClass__Ljava_lang_Class(Thread& t,Invocation& i){
        ReferencePtr ref = i.getReference(0);
        const ReferenceType& type = ref->getHandle()->getType();
        const Class& cl = type.getClass();
        ReferencePtr o = cl.getClassObject();
        return reinterpret_cast<jclass>(&(*o));
      }
      static void wait_I_V(Thread& t,Invocation& i){
        ReferencePtr ref = i.getReference(0);
        if(i.getMonitor()!=ref){
          i.pushReference(Objects::newInstance(Class("java/lang/IllegalMonitorStateException")));
          i.dup();
          MethodHandle handle("java/lang/IllegalMonitorStateException","<init>",{"Ljava/lang/String;"},VOID);
          i.pushReference(StringHelper::fromUtf8("The Current thread does not own this object"));
          handle.invokespecial(i);
          i.throwException();
        }
        t.clearMonitor(ref);
        t.setStatus(WAITING);
        t.setHandler(ref);
        t.nativeWait();//Uses a combination of setjmp and longjmp to go to the next thread until the handler is notified (or the thread is interrupted)
        if(t.interrupted()){
          i.pushReference(Objects::newInstance(Class("java/lang/InterruptedException")));
          i.dup();
          MethodHandle handle("java/lang/InterruptedException","<init>",{},VOID);
          handle.invokespecial(i);
          i.throwException();
        }
        t.setMonitor(ref);
        t.setStatus(NORMAL);
      }
    };
  };


};
