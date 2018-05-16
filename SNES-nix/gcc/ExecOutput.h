#ifndef __ExecOutput_h_2018_05_16_12_23
#define __ExecOutput_h_2018_05_16_12_23
#include <stdint.h>

struct symbol{
  uint16_t nameLen;
  uint8_t unlinked;
  uint32_t address;
  char name[];
};

struct section{
  uint16_t nameLen;
  uint64_t fpos;
  uint32_t length;
  uint32_t startAddr;
  uint8_t flags;
  char name[];
};

struct filemeta{
  uint8_t type;
  uint16_t length;
  uint8_t data[];
};

struct symbolmeta{
  uint16_t symbol;
  uint8_t type;
  uint16_t length;
  uint8_t data[];
};

struct MD_SourceFile{
  uint8_t type;
  uint16_t length;
  uint16_t sourceNo;
  char sourceLanguage[4];
  char fileName[];
};

struct MD_DynamicLibrary{
  uint8_t type;
  uint16_t length;
  char path[];
};

struct SymMD_Extern{
  uint16_t symbol;
  uint8_t type;
  uint16_t length;
};

struct SymMD_Visibility{
  uint16_t symbol;
  uint8_t type;
  uint16_t length;
  uint8_t visibility;
};

struct SymMD_NoReturn{
  uint16_t symbol;
  uint8_t type;
  uint16_t length;
};

struct SymMD_NativeCall{
  uint16_t symbol
  uint8_t type;
  uint16_t length;
};

struct SymMD_CallingConvention{
  uint16_t symbol;
  uint8_t type;
  uint16_t length;
  char convention[];
};

struct SymMD_LinkageType{
  uint16_t symbol;
  uint8_t type;
  uint16_t length;
  char type[4];
};

struct SymMD_SourceFile{
  uint16_t symbol;
  uint8_t type;
  uint16_t length;
  uint16_t fileNo;
  uint32_t lineNo;
};

struct SymMD_DeclType{
  uint16_t symbol;
  uint8_t type;
  uint16_t length;
  char typename[];
};

struct SymMD_TemplateParameter{
  uint16_t symbol;
  uint8_t  type;
  uint16_t length;
  uint8_t pos;
  uint8_t isVarargs;
  char declTypeAndName[];
};

struct SymMD_FunctionParameter{
  uint16_t symbol;
  uint8_t type;
  uint16_t length;
  uint8_t pos;
  uint8_t inRegister;
  char declTypeAndName[];
};

struct SymMD_VarargsFunction{
  uint16_t symbol;
  uint8_t type;
  uint16_t length; 
};

struct SymMD_LocalVariable{
  uint16_t symbol;
  uint8_t type;
  uint16_t length;
  uint8_t flags;
  uint16_t bpOffsetOrSymbol;
  char declTypeAndName[];
};

struct SymMD_LambdaFunction{
  uint16_t symbol;
  uint8_t type;
  uint16_t length;
  uint8_t flags; 
  uint16_t nCaptures;
  uint16_t ownerSymbol;
}; 

struct SymMD_LambdaCapture{
  uint16_t symbol;
  uint8_t type;
  uint16_t length;
  uint8_t flags;
  uint16_t bpOffsetOrSymbol;
};


struct SymMD_ClassField{
  uint16_t symbol;
  uint8_t type;
  uint16_t length;
  uint16_t offset;
  uint8_t flags;
  uint8_t reserved[3];
  char declTypeAndName[];
};

struct SymMD_ClassMethod{
  uint16_t symbol;
  uint8_t type;
  uint16_t length;
  uint8_t flags;
  uint16_t reserved[3];
  uint16_t symbolOrVtableEntry;
  char declTypeAndName[];
};

struct SymMD_VTableOffset{
  uint16_t symbol;
  uint8_t type;
  uint16_t length;
  
};


#endif
