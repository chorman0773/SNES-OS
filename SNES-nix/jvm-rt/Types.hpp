#ifndef __Types_hpp
#include <string>
using std::string;
namespace java{
    class ClassFile;
    class Class;


    enum class TypeCategory{
        Cat32 = 1, Cat64 = 2, CatReference = 99,
        CatVoid = 0
    };
    
    enum class Primitive{
        Z, B, S, C, I, F, J, D
    };

    class Type{
        virtual bool isPrimitive()const=0;
        virtual TypeCategory getCategory()const=0;
        virtual const string& getDescriptor()const=0;
        virtual const Type& getActualType()const;
    };
    
    class ReferenceType:public Type{
        string name;
        Class* base;
    public:
        ReferenceType(const string&,Class*);
        TypeCategory getCategory()const override final;
        bool isPrimitive()const override final;
        const string& getDescriptor()const override;
        const Class* getClass();
    };

    class ClassType final:public ReferenceType{
    public:
        ClassType(Class*);
        ClassType();
        
    };
    
    
    
    class PrimitiveType: public Type{
    public:
        bool isPrimitive()const override final;
        const string& getDescriptor() const override final;
        TypeCategory getCategory()const override final;
    };
    class SmallPrimitiveType final:public PrimitiveType{
    private:
        Primitive base;
        string desc;
    public:
        SmallPrimitiveType(const Primitive&,const string&);
        const Type& getActualType() const override;
    };
    
    class WordPrimitiveType final: public PrimitiveType{
    private:
        Primitive base;
        string desc;
    public:
        WordPrimitiveType(const Primitive&,const string&);
    };
    
    class DWordPrimitiveType final: public PrimitiveType{
    private:
        Primitive base;
        string desc;
    public:
        DWordPrimitiveType(const Primitive&,const string&);
        
    };
    
    class ArrayType final: public ReferenceType{
    private:
        const Type& base;
    public:
        ArrayType(const Type&);
    };
    
    class VoidType final:public Type{
    public:
        string& getDescriptor()const override;
        TypeCategory getCategory()const override;
        bool isPrimitive()const override;
    };
    
    
    class TypeDescriptor final{
    private:
        const Type& type;
        string desc;
    public:
        TypeDescriptor(const string&);
        const Type& getType()const;
        const string& getDesc()const;
    };
    
    
    const SmallPrimitiveType BOOLEAN(Primitive::Z,"Z");
    const SmallPrimitiveType BYTE(Primitive::B,"B");
    const SmallPrimitiveType SHORT(Primitive::S,"S");
    const SmallPrimitiveType CHAR(Primitive::C,"C");
    const WordPrimitiveType  INT(Primitive::I,"I");
    const WordPrimitiveType  FLOAT(Primitive::F,"F");
    const DWordPrimitiveType DOUBLE(Primitive::D,"D");
    const DWordPrimitiveType LONG(Primitive::J,"J");
    const VoidType           VOID;
    
    const ArrayType BOOLEANARRAY(BOOLEAN);
    const ArrayType BYTEARRAY(BYTE);
    const ArrayType SHORTARRAY(SHORT);
    const ArrayType CHARARRAY(CHAR);
    const ArrayType INTARRAY(INT);
    const ArrayType FLOATARRAY(FLOAT);
    const ArrayType DOUBLEARRAY(DOUBLE);
    const ArrayType LONGARRAY(LONG);
    
    const Type& getTypeFromDescriptor(const TypeDescriptor&);
};
#endif
