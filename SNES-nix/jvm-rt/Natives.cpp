#include "jni/jni.h"
#include "References.hpp"
#include "Invocation.hpp"
#include "Methods.hpp"
#include "Objects.hpp"
#include "Threads.hpp"
#include "Helpers.hpp"
#include "VMController.hpp"

namespace java{
  struct lang{
    struct Object{
      static jint hashCode_I(Thread& t,Invocation& i){
        ReferencePtr ref = i.getReference(0);
        return static_cast<jint>(ref->getHandle());
      }
      static jclass getClass__Ljava_lang_Class_2(Thread& t,Invocation& i){
        ReferencePtr ref = i.getReference(0);
        const ReferenceType& type = ref->getHandle()->getType();
        const Class& cl = type.getClass();
        ReferencePtr o = cl.getClassObject();
        return reinterpret_cast<jclass>(o.getReference());
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
        t.clearMonitor(ref->getHandle());
        t.setStatus(WAITING);
        t.setHandler(ref->getHandle());
        t.nativeWait(i.getInt(1));//Uses a combination of setjmp and longjmp to go to the next thread until the handler is notified (or the thread is interrupted)
        if(t.interrupted()){
          i.pushReference(Objects::newInstance(Class("java/lang/InterruptedException")));
          i.dup();
          MethodHandle handle("java/lang/InterruptedException","<init>",{},VOID);
          handle.invokespecial(i);
          i.throwException();
        }
        t.enterMonitor(ref->getHandle());
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
        t.notifyWaitingThread(ref->getHandle());
      }
      static void notifyAll_V(Thread& t,Invocation& i){
        ReferencePtr ref = i.getReference(0);
        if(i.getMonitor()!=ref->getHandle()){
          i.pushReference(Objects::newInstance(Class("java/lang/IllegalMonitorStateException")));
          i.dup();
          MethodHandle handle("java/lang/IllegalMonitorStateException","<init>",{"Ljava/lang/String;"},VOID);
          i.pushReference(StringHelper::fromUtf8("The Current thread does not own this object"));
          handle.invokespecial(i);
          i.throwException();
        }
        t.notifyAllThreads(ref->getHandle());
      }
     static jobject clone_Ljava_lang_Object_2(Thread& t,Invocation& i){
       ReferencePtr ref = i.getReference(0);
       if(!Objects::instanceof(ref,Class("java/lang/Cloneable")){
        i.pushReference(Objects::newInstance(Class("java/lang/CloneNotSupportedException")));
        i.dup();
        MethodHandle handle("java/lang/CloneNotSupportException","<init>",{},VOID);
        handle.invokespecial(i);
        i.throwException();
        return nullptr;
       }
       ReferencePtr ret = Objects::newInstance(h.getType().getClass());
       Objects::clone(ret,ref);
       return reinterpret_cast<jobject>(&(*ret));
     }
    };
    struct Runtime{
       static void halt_I(Thread& t,Invocation& i){
         int code = i.getInteger(1);
         std::exit(code);
       }
      static void exit_I(Thread& t,Invocation& i){
       int code = i.getInteger();
       VM::cleanupJVM();
       for(ReferencePtr ref:VM::getShutdownHooks()){
        MethodHandle startHandle("java/lang/Thread","start",{},VOID);
        MethodHandle joinHandle("java/lang/Thread","join",{},VOID);
        i.pushReference(ref);
        i.dup();
        startHandle.invoke(i);
        joinHandle.invoke(i);
       }
       if(VM::isRunFinalizersOnExitEnabled())
        VM::runGarbageCollection();
       std::exit(code);
      }
       
    };
    struct Thread{
      static jobjectArray getStackTrace(Thread& t,Invocation& i){
        StackTraceArray stArray = t.getStackTrace(); 
        ReferencePtr ret = Arrays::newReferenceArray(Class("java/lang/StackTraceElement"),stArray.length());
        int i = 0;
        for(const StackTraceElement& stElement:stArray){
          ReferencePtr elementValue = Objects::newReference(Class("java/lang/StackTraceElement"));
          MethodHandle handle("java/lang/StackTraceElement","<init>",{Objects::StringType,Objects::StringType,Objects::StringType,Objects::StringType,Objects::StringType,Objects::StringType,Objects::StringType,INT},VOID);
          i.pushObject(elementValue);
          i.pushObject(StringHelper::fromStlUtf8(stElement.getLoader()));
          i.pushObject(StringHelper::fromStlUtf8(stElement.getModule().getName()));
          i.pushObject(StringHelper::fromStlUtf8(stElement.getModule().getVersion()));
          i.pushObject(StringHelper::fromStlUtf8(stElement.getClass().getSourceName()));
          i.pushObject(StringHelper::fromStlUtf8(stElement.getMethod().getSourceName()));
          i.pushInteger(stElement.getLineNumber());
          handle.invoke(i);
          Arrays.storeObject(ret,elementValue,i++);
        }
        return reinterpret_cast<jobjectArray>(ret->getHandle());
      }
      static void start0(Thread& t,Invocation& i){
        
      }
      static void runThread(ReferencePtr thread){
        
      }
    };
  };
  
  template<typename RetT> RetT callNativeMethod(RetT(*fptr)(Thread&,Invocation&)){
     Thread& t = Thread::current();
     Invoction& i = t.getInvocationStack().getCurrentFrame().getInvocation();
     return fptr(t,i);
  }
  template<> void callNativeMethod<void>(void(*fptr)(Thread&,Invocation&)){
    Thread& t = Thread::current();
    Invoction& i = t.getInvocationStack().getCurrentFrame().getInvocation();
    fptr(t,i);
  }
  
  using voidNativeFp = void(*)(Thread&,Invocation&);
  using intNativeFp = jint(*)(Thread&,Invocation&);
  using floatNativeFp = jfloat(*)(Thread&,Invocation&);
  using longNativeFp = jlong(*)(Thread&,Invocation&);
  using booleanNativeFp = jboolean(*)(Thread&,Invocation&);
  using byteNativeFp = jbyte(*)(Thread&,Invocation&);
  using shortNativeFp = jshort(*)(Thread&,Invocation&);
  using charNativeFp = jchar(*)(Thread&,Invocation&);
  using doubleNativeFp = jdouble(*)(Thread&,Invocation&);
  using arrayNativeFp = jarray(*)(Thread&,Invocation&);
  using objectArrayNativeFp = jobjectArray(*)(Thread&,Invocation&);
  using booleanArrayNativeFp = jbooleanArray(*)(Thread&,Invocation&);
  using byteArrayNativeFp = jbyteArray(*)(Thread&,Invocation&);
  using shortArrayNativeFp = jshortArray(*)(Thread&,Invocation&);
  using charArrayNativeFp = jcharArray(*)(Thread&,Invocation&);
  using intArrayNativeFp = jintArray(*)(Thread&,Invocation&);
  using longArrayNativeFp = jlongArray(*)(Thread&,Invocation&);
  using floatArrayNativeFp = jfloatArray(*)(Thread&,Invocation&);
  using doubelArrayNativeFp = jdoubleArray(*)(Thread&,Invocation&);
  using classNativeFp = jclass(*)(Thread&,Invocation&);
  using stringNativeFp = jstring(*)(Thread&,Invocation&);
  using throwableNativeFp = jthrowable(*)(Thread&,Invocation&);
          
  voidNativeFp voidNatives[] = {&lang::Object::wait_I_V,&lang::Object::notify__V,&lang::Object::notifyAll__V,&lang::Runtime::halt__I
  
};
