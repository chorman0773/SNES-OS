#ifndef __ExecutableLaunch_h_2018_04_17_13_31
#define __ExecutableLaunch_h_2018_04_17_13_31

#define ELF_MAGIC 0x1B697670
#define LIB_MAGIC  0x1B767366

#include <stdio.h>

enum symboltype{
	FEILD, FUNCTION, DUMMY, TYPE
};

enum accessmode{
	hidden, protect, internal, normal
};

enum bin_type{
	c, assembly, cpp
};


typedef struct _symbol{
	const char symName[128];
	enum symboltype type;
	enum accessmode mode;
	void* addr;
}symbol;




typedef struct _plt_entry{
	symbol* sym;
	symbol* target;
	void* mem;
}plt_entry;

typedef struct _binary_descriptor{
	int magic;
	int version;
	enum bin_type type;
	int symtblSize;
	int cdataSize;
	int dataSize;
	int execSize;
}binary_descriptor;


typedef struct _type_descriptor{
	int vtableSize;
	symbol* vtable;
	symbol* ctor;
	symbol* dtor;
	int size;
}type_descriptor;



int run(FILE*,const char**,int);

bool validateElf(FILE*);
bool validateLib(FILE*);

binary_descriptor readHeader(FILE*);
symbol* openSymbols(FILE*);
type_descriptor getTypeInfo(FILE*,const char*);

void* link(FILE*,const char*);


#endif