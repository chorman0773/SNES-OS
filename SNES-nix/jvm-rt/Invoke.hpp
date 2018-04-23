#ifndef __Invoke_hpp_2018_04_23_09_11
#define __Invoke_hpp_2018_04_23_09_11
#include <memory>
using std::shared_ptr;
namespace java{
    class Class; 
    class ReferencePtr;
    class Invocation;
    class Type;
    class MethodDescriptor;
    
    struct StackValue{
        Type& type;
        int cookie;
        union{
            int   iVal;
            float fVal;
            int   bytes;
            shared_ptr<ReferencePtr> ref;
            void* empty;
        }value;
        StackValue* boundTo;
        StackValue(Type&,int);
        StackValue(Type&,float);
        StackValue(Type&,uint64_t);
        StackValue(Type&,double);
        StackValue(Type&,uint64_t,const StackValue*);
        StackValue(Type&,double,const StackValue*);
        StackValue(Type&,shared_ptr<ReferencePtr>&);
        StackValue();
        bool isValid();
    };
    struct FrameStack{
        int sp;
        StackValue  stack[256];
    };
    class StackFrame{
        Invocation& invoke;
        int maxStack;
        int maxLocals;
        FrameStack frame;
    public:
        StackFrame(Invocation&,int,int);
        StackFrame(Invocation&);
        StackValue& getLocal(int);
        StackValue& pop();
        void pop2(StackValue&,StackValue&);
        void push(StackValue&);
        void push2(StackValue&);
        void dup();
        void dup2();
    };
    class ThrownException{
        StackValue except;
    public:
        ThrownException(StackValue&);
        StackFrame& catchIn(Invocation&);
        void cleanUp(Invocation&);
    };
    
    class Invocation{
    private:
        StackFrame currFrame;
        Invocation* returnTarget;
        int pc;
        MethodDescriptor& desc;
    public:
        Invocation(MethodDescriptor&,Invocation*);
        StackFrame& getCurrentFrame();
        StackFrame& returnVoid();
        StackFrame& returnWordValue();
        StackFrame& returnDWordValue();
        ThrownException& throwException();
        void returnTo();
        void abruptReturnTo(ThrownException&);
        bool canCatch(ThrownException&);
        StackFrame& getHandlerFor(ThrownException&);
        uint8_t read8();
        uint16_t read16();
        uint32_t read32();
        
        void pushInt(int32_t);
        int32_t popInt();
        void pushFloat(float);
        float popFloat();
        void pushLong(long);
        long popLong();
        void pushDouble(double);
        double popDouble();
        void pushReference(shared_ptr<ReferencePtr>);
        shared_ptr<ReferencePtr> popReference();
        
        void setInt(int,int32_t);
        int32_t getInt(int);
        void setFloat(int,float);
        float getFloat(int);
        void setDouble(int,double);
        double getDouble(int);
        void setLong(int,long);
        long getLong(int);
        
        
    };
    
    namespace bytecode{
        class Instruction{
        public:
            virtual void apply(Invocation&)=0;
        };
        class NopInstruction final:public Instruction{
        public:
            void apply(Invocation&);
        };
        class IConstInstruction final:public Instruction{
        private:
            int value;
        public:
            IConstInstruction(int);
            void apply(Invocation&); 
        };
        class LdcInstruction final:public Instruction{
        public:
            void apply(Invocation&);
        };
        class BiPushInstruction final:public Instruction{
        public:
            void apply(Invocation&);
        };
        class SiPushInstruction final:public Instruction{
        public:
            void apply(Invocation&);
        };
        class FConstInstruction final:public Instruction{
            float val;
        public:
            FConstInstruction(float);
            void apply(Invocation&);
        };
        class LConstInstruction final:public Instruction{
            long val;
        public:
            LConstInstruction(long);
            void apply(Invocation&);
        };
        class DConstInstruction final:public Instruction{
            double val;
          public:
            DConstInstruction(double);
            void apply(Invocation&);
        };
        
    };
  
};
#endif
