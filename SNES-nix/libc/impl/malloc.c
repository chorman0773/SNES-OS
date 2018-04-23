#include "../stdlib.h"
#include "../stdbool.h"

typedef struct _block{
    int size;
    bool isFree;
    struct _block* nextBlock;
}block;
extern void* heap;
extern block* firstBlock;
extern block* heapBlock;
extern int heapLength;

void* malloc(size_t size){
    void* out = NULL;
    block* next = heapBlock;
    int nLen = heapBlock->size;
    unsigned heapPos = (unsigned) heap;
    int i;
    for(i = 0;i<32;i++){
       if(heapBlock->size>=size){
            out = heapBlock+1;
            heapBlock = heapBlock->nextBlock;
        }else if(heapBlock->nextBlock==NULL){
            out = (void*) (heapBlock+1);
            next = (block*)(out+size); 
            nLen += ((unsigned)next)+sizeof(block);
            if(nLen<0){
                heapBlock = firstBlock;
                next = firstBlock;
                continue;
            }
            heapBlock->nextBlock = next;
            heapBlock =next;
            next->isFree = true;
            next->nextBlock = NULL;
            next->size = nLen;
        }
        else{
            next = next->nextBlock;
            if(next->isFree){
                nLen += sizeof(block)+next->size;
                heapBlock->nextBlock = next->nextBlock;
                heapBlock->size = nLen;
            }
        }
    }
    
    return out;
}
void* calloc(size_t elementSize,size_t count){
    return malloc(elementSize*count);
}

void free(void* v){
    block* b = (block*)v;
    b = b-1;
    b->isFree = true;
}


void* realloc(void* ptr,size_t s){
    block* b = ((block*)ptr)-1;
    block* next = b->nextBlock;
    size_t currSize = b->size;
    if(b->size>=s)
        return ptr;
    else if(next==NULL){
        b->nextBlock = NULL;
        free(ptr);
        return malloc(s);
    }
    else while(next->isFree){
        currSize += next->size+sizeof(block);
        next = next->nextBlock;
        b->size = currSize;
        if(currSize>=s)
            return ptr;
        else if(next==NULL){
            b->nextBlock = NULL;
            b->size = currSize;
            free(ptr);
            return malloc(s);
        }
    }
    free(ptr);
    return malloc(s);
}



