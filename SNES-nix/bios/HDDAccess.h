#include "stddef.h"

    int open(const char*,int);
    void close(int);
    void write(int,const void*,size_t);
    int read(int,void*,size_t);
    
    void unlink(const char*);
    void relink(const char*,const char*);
    const char* tmpname();
