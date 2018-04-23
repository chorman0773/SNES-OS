#ifndef __Symbols_h_2018_04_23_12_09
#define __Symbols_h_2018_04_23_12_09

enum symboltype{
	FEILD, FUNCTION, DUMMY, TYPE
};

enum accessmode{
	hidden, protect, internal, normal
};

typedef struct{
    symboltype type;
    accessmode mode;
    char name[256];
}symbol;

typedef struct{
    char name[128];
}field;

typedef struct{
    char name[128];
}c_method;


#endif
