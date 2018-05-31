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
    using ReferencePtr = weak_pointer<Handle>;
    
    enum class Reachability{
        UNREACHABLE, PHANTOM, WEEK, SOFT, STRONG
    };
    
    class GarbageCollector{
    private:
        vector<shared_ptr<Handle>> references;
    public:
        GarbageCollector();
        ReferencePtr constructReference(ReferenceType&,int);
        Reachability getReachabilityFor(Handle*);
        void collectGarbage();
        void finalizeObject(Handle*);
    };
    
};

#endif
