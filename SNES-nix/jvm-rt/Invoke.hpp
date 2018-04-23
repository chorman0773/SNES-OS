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
	
	enum class CompareOp{
		LT, LE, EQ, NE, GE, GT
	};
	
	enum class UnaryOp{
		UMN, BNOT
	};
	
	enum class BinaryOp{
		ADD, SUB, DIV, MUL, REM,
		BAND, BOR, BXOR, LSH, RSH, ARSH
	};
	
	
    struct StackValue{
        StackValueType type;
        int cookie;
        union{
            int   iVal;
            float fVal;
            int   bytes;
            shared_ptr<ReferencePtr> ref;
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
        void pushReference(shared_ptr<ReferencePtr>);
        shared_ptr<ReferencePtr> popReference();
        void setMonitor(shared_ptr<ReferencePtr>);
        void clearMonitor();
        
        void setInt(int,int32_t);
        int32_t getInt(int);
        void setFloat(int,float);
        float getFloat(int);
        void setDouble(int,double);
        double getDouble(int);
        void setLong(int,long);
        long getLong(int);
        
        
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
        class NopInstruction final:public Instruction{
        public:
            void apply(Invocation&);
			bool validate(ValidationState&);
        };
        class IConstInstruction final:public Instruction{
        private:
            int value;
        public:
            IConstInstruction(int);
            void apply(Invocation&);
			bool validate(ValidationState&);			
        };
        class LdcInstruction final:public Instruction{
        public:
            void apply(Invocation&);
			bool validate(ValidationState&);
        };
        class BiPushInstruction final:public Instruction{
        public:
            void apply(Invocation&);
			bool validate(ValidationState&);
        };
        class SiPushInstruction final:public Instruction{
        public:
            void apply(Invocation&);
			bool validate(ValidationState&);
        };
        class FConstInstruction final:public Instruction{
            float val;
        public:
            FConstInstruction(float);
            void apply(Invocation&);
			bool validate(ValidationState&);
        };
        class LConstInstruction final:public Instruction{
            long val;
        public:
            LConstInstruction(long);
            void apply(Invocation&);
			bool validate(ValidationState&);
        };
        class DConstInstruction final:public Instruction{
            double val;
          public:
            DConstInstruction(double);
            void apply(Invocation&);
			bool validate(ValidationState&);
        };
		class AConstNullInstruction final:public Instruction{
		public:
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		
		class ToSmallPrimitiveInstruction final:public Instruction{
			const PrimitiveType& target;
		public:
			ToSmallPrimitiveInstruction(const PrimitiveType&);
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		
		class WidenPrimitiveInstruction final:public Instruction{
			StackValueType base;
			StackValueType target;
		public:
			WidenPrimitiveInstruction(StackValueType,StackValueType);
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		
		class NarrowPrimitiveInstruction final:public Instruction{
			StackValueType base;
			StackValueType target;
		public:
			NarrowPrimitiveInstruction(StackValueType,StackValueType);
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		
		class LoadValue final:public Instruction{
			StackValueType target;
        public:
			LoadValue(StackValueType);
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		class LoadValue_n final:public Instruction{
			StackValueType target;
			int n;
		public:
			LoadValue_n(StackValueType,int);
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		class ArrayLoadValue final:public Instruction{
			StackValueType target;
		public:
			ArrayLoadValue(StackValueType);
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
        class StoreValue final:public Instruction{
			StackValueType target;
        public:
			StoreValue(StackValueType);
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		class StoreValue_n final:public Instruction{
			StackValueType target;
			int n;
		public:
			StoreValue_n(StackValueType,int);
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		class ArrayStoreValue final:public Instruction{
			StackValueType target;
		public:
			ArrayStoreValue(StackValueType);
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		
		class SmallPrimitiveArrayLoad final:public Instruction{
			ArrayType& type;
		public:
			SmallPrimitiveArrayLoad(ArrayType&);
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		class SmallPrimitiveArrayStore final:public Instruction{
			ArrayType& type;
		public:
			SmallPrimitiveArrayStore(ArrayType&);
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		
		class ANewArray final:public Instruction{
		public:
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		
		class ValueReturn final:public Instruction{
			StackValueType type;
		public:
			ValueReturn(StackValueType);
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		class VoidReturn final:public Instruction{
		public:
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		
		class ArrayLength final:public Instruction{
		public:
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		
		class ThrowExcept final:public Instruction{
		public:
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		
		class CheckCast final:public Instruction{
		public:
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		
		class IsInstance final:public Instruction{
		public:
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		
		class UnaryOpInstruction final:public Instruction{
			StackValueType target;
			UnaryOp op;
		public:
			UnaryOpInstruction(StackValueType,UnaryOp);
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		
		class BinaryOpInstruction final:public Instruction{
			StackValueType target;
			BinaryOp op;
		public:
			BinaryOpInstruction(StackValueType,BinaryOp);
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		
		class CompareInstruction final:public Instruction{
			StackValueType target;
			CompareOp op;
		public:
			CompareInstruction(StackValueType,CompareOp);
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		class BooleanCompareInstruction final:public Instruction{
			CompareOp op;
		public:
			BooleanCompareInstruction(CompareOp);
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		
		class Pop final:public Instruction{
		public:
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		
		class GetField final:public Instruction{
		public:
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		class PutField final:public Instruction{
		public:
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		class GetStatic final:public Instruction{
		public:
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		class PutStatic final:public Instruction{
		public:
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
		
		class Goto final:public Instruction{
		public:
			void apply(Invocation&);
			bool validate(ValidationState&);
		};
        
        
        
        class InvokeInstruction final:public Instruction{
            InvocationType type;
        public:
            InvokeInstruction(InvocationType);
            void apply(Invocation&);
			bool validate(ValidationState&);
        };
        
        class JsrInstruction final:public Instruction{
        public:
            void apply(Invocation&);
			bool validate(ValidationState&);
        };
        class RetInstruction final:public Instruction{
        public:
            void apply(Invocation&);
			bool validate(ValidationState&);
        };

        class ImplDepInstruction final:public Instruction{
            int key;
        public:
            ImplDepInstruction(int);
            void apply(Invocation&);
			bool validate(ValidationState&);
        };
        class BreakpointInstruction final:public Instruction{
        public:
            void apply(Invocation&);
			bool validate(ValidationState&);
        };
        
        class SwapInstruction final:public Instruction{
        public:
            void apply(Invocation&);
			bool validate(ValidationState&);
        };
        
        class MonitorEnter final:public Instruction{
        public:
            void apply(Invocation&);
			bool validate(ValidationState&);
        };
        class MonitorExit final:public Instruction{
        public:
            void apply(Invocation&);
			bool validate(ValidationState&);
        };
        class PopInstruction final:public Instruction{
            int num;
        public:
            PopInstruction(int);
            void apply(Invocation&);
			bool validate(ValidationState&);
        };
		
        class MultiANewArray final:public Instruction{
        public:
            void apply(Invocation&);
			bool validate(ValidationState&);
        };
        
        class NewInstruction final:public Instruction{
        public:
            void apply(Invocation&);
			bool validate(ValidationState&);
        };
        
    };
  
};
#endif
