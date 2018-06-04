#include "Invoke.hpp"
#include "ClassFile.hpp"
#include "Types.hpp"
#include "Objects.hpp"

int32_t signExtend(int8_t val){
  return (int32_t)(((((uint64_t)((uint8_t)val))>>7)<<32)-1)|val;
}
int32_t signExtend(int16_t val){
  return (int32_t)(((((uint64_t)((uint8_t)val))>>15)<<32)-1)|val;
}

int32_t zeroExtend(uint16_t val){
	return ((int32_t)val)&0xFFFF;
}

namespace java{
  namespace bytecode{
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
    
	class NopInstruction final:public Instruction{
	public:
		void apply(Invocation& i){
          
        }
				bool validate(ValidationState& v){
          return true;
        }
	};
	class IConstInstruction final:public Instruction{
	private:
		int32_t value;
	public:
		IConstInstruction(int32_t val){
        	  value = val;
		}
		void apply(Invocation& i){
			i.pushInt(value);
		}
		bool validate(ValidationState& v){
          return v.canPush({INT});
        }
	};
	class LdcInstruction final:public Instruction{
	public:
		void apply(Invocation& i){
          int target = i.read16();
          
	}
				bool validate(ValidationState&);
			};
	class BiPushInstruction final:public Instruction{
		public:
		void apply(Invocation& i){
          int32_t val = signExtend(i.read8());
          i.pushInt(val);
        }
		bool validate(ValidationState& v){
          if(!v.canRead8())
            return false;
           return v.canPush({B});
        }
	};
	class SiPushInstruction final:public Instruction{
	public:
		void apply(Invocation& i){
			int32_t val = signExtend(i.read16());
			i.pushInt(val);
		}
		bool validate(ValidationState& v){
			if(!v.canRead16())
				return false;
			return v.canPush({S});
		}
	};
	class FConstInstruction final:public Instruction{
		float val;
	public:
		FConstInstruction(float val):val(val){}
		void apply(Invocation& i){
			i.pushFloat(val);	
		}
		bool validate(ValidationState& v){
			return v.canPush({F});	
		}
	};
	class LConstInstruction final:public Instruction{
		long long val;
	public:
		LConstInstruction(long long val):val(val){}
		void apply(Invocation& i){
			i.pushLong(val);
		}
		bool validate(ValidationState& v){
			return v.canPush({L});	
		}
	};
	class DConstInstruction final:public Instruction{
		double val;
	public:
		DConstInstruction(double val):val(val){}
		void apply(Invocation& i){
			i.pushDouble(val);	
		}
		bool validate(ValidationState& v){
			return v.canPush({D});	
		}
	};
	class AConstNullInstruction final:public Instruction{
	public:
		void apply(Invocation& i){
			i.pushReference(null);	
		}
		bool validate(ValidationState& v){
			return v.canPush({nulltype});	
		}
	};

	class ToSmallPrimitiveInstruction final:public Instruction{
		const SmallPrimitiveType& target;
	public:
		ToSmallPrimitiveInstruction(const SmallPrimitiveType& target):target(target){}
		void apply(Invocation& i){
			int32_t val = i.popInt();
			if(&target==&B)
				i.pushInt(signExtend(val&0xFF));
			else if(&target==&S)
				i.pushInt(signExtend(val&0xFFFF));
			else
				i.pushInt(zeroExtend(val&0xFFFF));
		}
		bool validate(ValidationState& v){
			return v.canReplace({I},{target});	
		}
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
		void apply(Invocation& i){
			
		}
		bool validate(ValidationState& v){
			
		}
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
		void apply(Invocation& i){
            
        }
		bool validate(ValidationState& v){
         return v.canPop({ClassType(Class("java/lang/Throwable"))});   
        }
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
		ImplDepInstruction(int key){
			this->key = key;	
		}
		void apply(Invocation& i){
			
		}
		bool validate(ValidationState& v){
			return false;	
		}
	};
	class BreakpointInstruction final:public Instruction{
	public:
		void apply(Invocation& i){
				
		}
		bool validate(ValidationState& v){
			return false;	
		}
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

