#ifndef __ClassFile_hpp_2018_04_23_08_28
#define __ClassFile_hpp_2018_04_23_08_28
#include <cstdint>
namespace java{
    
    enum class ConstantPoolEntryType{
        Utf8 = 1, Integer = 3, Float = 4, Long = 5, Double = 6, Class = 7,
        String = 8, Fieldref = 9, Methodref = 10, InterfaceMethodref = 11,
        NameAndType = 12, MethodHandle = 15, MethodType = 16, InvokeDynamic = 18,
        Module = 19, Package = 20
    }uint8_t;
    
    class Class;
    class TypeDescriptor;
    
    
    class SignatureDescriptor{
    private:
        TypeDescriptor retType;
        vector<TypeDescriptor> paramTypes;
    };
    
    class MethodDescriptor;
    class FieldDescriptor;
    
    union ConstantPayload{
            struct{
                uint16_t length;
                char value[];
            }const_utf8;
            struct{
                uint16_t nameIdx;
            }const_class;
            struct{
                uint16_t valueIdx;
            }const_string;
            struct{
                int32_t value;
            }const_int;
            struct{
                float value;
            }const_float;
            struct{
                double value;
            }const_double;
            struct{
                uint64_t value;
            }const_long;
    };
    
    struct Constant{
        ConstantPoolEntryType type;
        ConstantPayload  payload;
    };
    

};
#endif
