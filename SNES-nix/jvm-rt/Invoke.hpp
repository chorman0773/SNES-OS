#ifndef __Invoke_hpp_2018_04_23_09_11
#define __Invoke_hpp_2018_04_23_09_11
#include <memory>
#include <cstdint>
#include <stdint.h>
#include <initializer_list>
using std::shared_ptr;
using std::initializer_list;
namespace java{
    class Class; 
    class ReferencePtr;
    class Invocation;
    class Type;
    class MethodDescriptor;
	class PrimitiveType;
	class SmallPrimitiveType;
	class ArrayType;
    class Thread;
    
	enum class StackValueType{
		INT, FLOAT, REFERENCE, 
		LONG, DOUBLE, TOP,
		RETURNADDRESS, INVALID
	}uint8_t;
    
    enum class InvocationType;
	
	
	
	
    struct StackValue{
        StackValueType type;
        int cookie;
        union{
            int   iVal;
            float fVal;
            int   bytes;
            ReferencePtr ref;
			int retPc;
        }value;
        StackValue* boundTo;
        StackValue(int);
        StackValue(float);
        StackValue(uint64_t);
        StackValue(double);
        StackValue(uint64_t,const StackValue*);
        StackValue(double,const StackValue*);
        StackValue(shared_ptr<ReferencePtr>&);
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
        void pop(StackValue&);
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
        Thread& execThread;
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
        
        void dup();
        void dup_x();
        void dup2();
        void swap();
        void del();
        
        void pushInt(int32_t);
        int32_t popInt();
        void pushFloat(float);
        float popFloat();
        void pushLong(long);
        long popLong();
        void pushDouble(double);
        double popDouble();
        void pushReference(ReferencePtr);
       	ReferencePtr popReference();
        void setMonitor(ReferencePtr);
        void clearMonitor();
        
        void setInt(int,int32_t);
        int32_t getInt(int);
        void setFloat(int,float);
        float getFloat(int);
        void setDouble(int,double);
        double getDouble(int);
        void setLong(int,long);
        long getLong(int);
        uint32_t getReturnAddress(int);
		void setReturnAddress(uint32_t,int);
        
    };
	
	struct VerificationValue{
		StackValueType stackType;
		Type* refType;
		VerificationValue(StackValueType);
		VerificationValue();
		VerificationValue(Type&);
		bool isValid();
	};
	
	class ValidationState{
		MethodDescriptor& desc;
		int classFileVersion;
		int maxStack;
		int maxLocals;
		int sp;
        	int pc;
		VerificationValue vstack[256];
	public:
		ValidationState(MethodDescriptor&);
		bool canPop(initializer_list<VerificationValue>&);
		bool canPush(initializer_list<VerificationValue>&);
		bool canReplace(initializer_list<VerificationValue>&,initializer_list<VerificationValue>&);
		bool canSetLocal(int,VerificationValue&);
		bool canGetLocal(int,VerificationValue&);
		bool canLoad(int,VerificationValue&);
		bool canStore(int,VerificationValue&);
		bool canReturn(VerificationValue&);
		bool canReturnVoid();
		bool canCall(MethodDescriptor&);
		bool canPopTypeless(int);
		bool canDup();
		bool canDupX(int);
		bool canDup2();
		bool canSwap();
		bool canJsr();
		bool canInvokeNonVirtual();
		uint8_t read8();
		uint16_t read16();
		uint32_t read32();
	};
    
    namespace bytecode{
       	class Instruction{
	public:
		virtual void apply(Invocation&)=0;
		virtual bool validate(ValidationState&)=0;
	};

    };
  
};
#endif
