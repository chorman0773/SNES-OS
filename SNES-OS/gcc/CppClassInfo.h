#ifndef __CppClassInfo_h_2018_05_18_18_50
#define __CppClassInfo_h_2018_05_18_18_50

typedef struct{
  unsigned short targetClass;
  unsigned short offset;
}class_structure_offset;

typedef struct{
  unsigned short length;
  class_structure_offset offsets[];
}class_offsettable;

#endif
