#ifndef __References_hpp_2018_04_23_08_56
#define __References_hpp_2018_04_23_08_56

#include <memory>

using std::shared_ptr;
using std::weak_ptr;

namespace java{
    class ReferenceType;
    class MethodHandle;
    
    struct Handle{
        ReferenceType& type;
        void* mem;
        const MethodHandle& finalizer;
        Handle(ReferenceType&,int);
        ~Handle();
    };
    
    enum class ReferenceKind{
      STRONG, SOFT, WEEK  
    };

    struct Reference{
        const virtual Handle* getHandle()const = 0;
        virtual bool isStrong()const=0;
        virtual ReferenceKind getType()const=0;
        virtual ~Reference();
    };
    struct WeakReference final:public Reference{
        weak_ptr<Handle> ref;
        WeakReference(shared_ptr<Handle>&);
        const Handle* getHandle()const;
        bool isReclaimed()const;
        ReferenceKind getType()const;
    };
    struct SoftReference final:public Reference{
        shared_ptr<Handle> base;
        SoftReference(shared_ptr<Handle>&);
        void freeSoftMemory();
        const Handle* getHandle()const;
        bool isReclaimed()const;
        ReferenceKind getType()const;
    };
    struct StrongReference final:public Reference{
        shared_ptr<Handle> base;
        StrongReference(ReferenceType&,int);
        StrongReference(shared_ptr<Handle>&);
        StrongReference();
        const Handle* getHandle()const;
        bool isReclaimable()const;
        ReferenceKind getType()const;
    };
    
    
    
    class ReferencePtr final{
    private:
        ReferenceType type;
        Reference* ref;
        ReferencePtr(Reference*);
    public:
        ReferencePtr(ReferenceType&,int);
        ~ReferencePtr();
        Reference& operator*();
        Reference* operator->();
        WeakReference& asWeak();
        SoftReference& asSoft();
        bool isValidCast(ReferenceType&);
    };
    
    const ReferencePtr null(nullptr);
};

#endif
