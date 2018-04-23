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

    struct Reference{
        const virtual Handle* getHandle()const = 0;
    };
    struct WeakReference final:public Reference{
        weak_ptr<Handle> ref;
        WeakReference(ReferenceType&,int);
        WeakReference();
        const Handle* getHandle()const;
        bool isReclaimed()const;
    };
    struct SoftReference final:public Reference{
        weak_ptr<Handle> weak;
        shared_ptr<Handle> base;
        SoftReference(ReferenceType&,int);
        SoftReference(shared_ptr<Handle>&);
        void freeSoftMemory();
        const Handle* getHandle()const;
        bool isReclaimed()const;
    };
    struct StrongReference final:public Reference{
        shared_ptr<Handle> base;
        StrongReference(ReferenceType&,int);
        StrongReference(shared_ptr<Handle>&);
        StrongReference();
        const Handle* getHandle()const;
    };
    
    class ReferencePtr final{
    private:
        Reference* ref;
    public:
        ReferencePtr(Reference*);
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
