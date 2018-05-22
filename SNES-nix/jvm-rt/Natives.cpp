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
        t.nativeWait(i.getInt(1));//Uses a combination of setjmp and longjmp to go to the next thread until the handler is notified (or the thread is interrupted)
        if(t.interrupted()){
          i.pushReference(Objects::newInstance(Class("java/lang/InterruptedException")));
          i.dup();
          MethodHandle handle("java/lang/InterruptedException","<init>",{},VOID);
          handle.invokespecial(i);
          i.throwException();
        }
        t.enterMonitor(ref);
        t.setStatus(NORMAL);
      }
      static void notify_V(Thread& t,Invocation& i){
        ReferencePtr ref = i.getReference(0);
        if(i.getMonitor()!=ref){
          i.pushReference(Objects::newInstance(Class("java/lang/IllegalMonitorStateException")));
          i.dup();
          MethodHandle handle("java/lang/IllegalMonitorStateException","<init>",{"Ljava/lang/String;"},VOID);
          i.pushReference(StringHelper::fromUtf8("The Current thread does not own this object"));
          handle.invokespecial(i);
          i.throwException();
        }
        t.notifyWaitingThread(ref);
      }
      static void notify_V(Thread& t,Invocation& i){
        ReferencePtr ref = i.getReference(0);
        if(i.getMonitor()!=ref){
          i.pushReference(Objects::newInstance(Class("java/lang/IllegalMonitorStateException")));
          i.dup();
          MethodHandle handle("java/lang/IllegalMonitorStateException","<init>",{"Ljava/lang/String;"},VOID);
          i.pushReference(StringHelper::fromUtf8("The Current thread does not own this object"));
          handle.invokespecial(i);
          i.throwException();
        }
        t.notifyAllThreads(ref);
      }
     static jobject clone_Ljava_lang_Object_(Thread& t,Invocation& i){
       ReferencePtr ref = i.getReference(0);
       if(!Objects::instanceof(ref,Class("java/lang/Cloneable")){
        i.pushReference(Objects::newInstance(Class("java/lang/CloneNotSupportedException")));
        i.dup();
        MethodHandle handle("java/lang/CloneNotSupportException","<init>",{},VOID);
        handle.invokespecial(i);
        i.throwException();
       }
       ReferencePtr ret = Objects::newInstance(h.getType().getClass());
       Objects::clone(ret,ref);
       return reinterpret_cast<jobject>(&(*ret));
     }
    };
  };

};
