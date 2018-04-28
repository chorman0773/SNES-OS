#ifndef __ClassFile_hpp_2018_04_23_08_28
#define __ClassFile_hpp_2018_04_23_08_28
#include <cstdint>
#include <initializer_list>
#include <vector>
#include <string>
#include <cstdio>
#include <type_traits>
#include <cstring>
using std::string;
using std::vector;
using std::initializer_list;
namespace java{
    class ClassFile;
    
    class FileReader{
        uint8_t* data;
        int loc;
        int len;
    public:
        FileReader(FILE*);
        void seekTo(int);
        uint8_t read8();
        uint16_t read16();
        uint32_t read32();
        uint64_t read64();
        float readFloat();
        double readDouble();
        template<typename E> std::enable_if<std::is_enum_v<E>,E> readEnum(){
            E val;
            int prev = loc;
            loc+=sizeof(E);
            memcopy(&val,data+prev,sizeof(E));
            return val;
        }
    };
    
    struct ModifiableType{
        uint16_t modifiers;
    };
    
    
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
        const TypeDescriptor& retType;
        vector<TypeDescriptor> paramTypes;
    public:
        SignatureDescriptor(const string&);
        SignatureDescriptor(const TypeDescriptor&,const initializer_list<TypeDescriptor>&);
    };
    
    class MethodDescriptor;
    class FieldDescriptor;
    class ClassDescriptor;
    
    union ConstantPayload{
            struct{
                uint16_t length;
                string value;
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
            struct{
                uint16_t name;
                uint16_t type;
            }const_NameAndType;
    };
    
    struct Constant{
        ConstantPoolEntryType type;
        ConstantPayload  payload;
        bool isLoadable();
    };
    
    enum class AccessType{
        OBJECT, STATIC
    };
    enum class InvocationType{
            VIRTUAL, STATIC, SPECIAL,
            DYNAMIC, INTERFACE
    };
    
    class AccessibleObject{
    private:
        const ClassFile& owner;
        int accessFlags;
    public:
        AccessibleObject(const ClassFile&,int);
        bool canAccess(const ClassFile&);
        bool isPublic();
        bool isProtected();
        bool isPrivate();
    };
    
    class NameAndType{
        string name;
        const TypeDescriptor& type;
    public:
        NameAndType(const string&,const TypeDescriptor&);
        const string& getName();
        const TypeDescriptor& getType();
        bool operator<(const NameAndType&)const;
        bool operator>(const NameAndType&)const;
        bool operator==(const NameAndType&)const;
        bool operator!=(const NameAndType&)const;
        bool operator<=(const NameAndType&)const;
        bool operator>=(const NameAndType&)const;
    };
    
    class NameAndSignature{
        string name;
        const SignatureDescriptor& signature;
    public:
        NameAndSignature(const string&,const SignatureDescriptor);
        const string& getName();
        const SignatureDescriptor& getSignature();
        bool operator< (const NameAndSignature&)const;
        bool operator> (const NameAndSignature&)const;
        bool operator==(const NameAndSignature&)const;
        bool operator!=(const NameAndSignature&)const;
        bool operator<=(const NameAndSignature&)const;
        bool operator>=(const NameAndSignature&)const;
    };
    

    
    class FieldDescriptor: public AccessibleObject{
    private:
        const ClassDescriptor& owner;
        AccessType type;
        const NameAndType& nameAndType;
    public:
        FieldDescriptor(const NameAndType&,const ClassDescriptor&,AccessType,short);
        AccessType getFieldAccessType()const;
        const NameAndType& getNameAndType()const;
        operator string()const;
        bool operator< (const FieldDescriptor&)const;
        bool operator> (const FieldDescriptor&)const;
        bool operator==(const FieldDescriptor&)const;
        bool operator!=(const FieldDescriptor&)const;
        bool operator<=(const FieldDescriptor&)const;
        bool operator>=(const FieldDescriptor&)const;
    };
    
    class MethodDescriptor: public AccessibleObject{
    private:
        const ClassDescriptor& owner;
        InvocationType type;
        const NameAndSignature& nameAndSignature;
        uint64_t codePos;
    public:
        MethodDescriptor(const NameAndSignature&,const ClassDescriptor&,InvocationType,uint64_t,short);
        InvocationType getInvocationType()const;
        const NameAndSignature& getNameAndSignature()const;
        operator string()const;
        bool operator< (const MethodDescriptor&)const;
        bool operator> (const MethodDescriptor&)const;
        bool operator==(const MethodDescriptor&)const;
        bool operator!=(const MethodDescriptor&)const;
        bool operator<=(const MethodDescriptor&)const;
        bool operator>=(const MethodDescriptor&)const;
    };
    

};
#endif
