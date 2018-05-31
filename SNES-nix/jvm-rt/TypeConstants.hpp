#ifndef __TypeConstants_hpp_2018_05_31_12_15
#define __TypeConstants_hpp_2018_05_31_12_15
#include "Types.hpp"
#include "Classes.hpp"

namespace java{
  ClassType object = ClassType(Class("java/lang/Object"));
  ClassType enum_class = ClassType(Class("java/lang/Enum"));
  ClassType class_class = ClassType(Class("java/lang/Class"));
  ClassType throwable = ClassType(Class("java/lang/Throwable"));
  ClassType string_class = ClassType(Class("java/lang/String"));
  ClassType methodhandle = ClassType(Class("java/lang/invoke/MethodHandle"));
  ClassType annotation = ClassType(Class("java/lang/annotation/Annotation"));
  ClassType thread_class = ClassType(Class("java/lang/Thread"));
  ClassType week_reference_class = ClassType(Class("java/lang/ref/WeakReference"));
  ClassType soft_reference_class = ClassType(Class("java/lang/ref/SoftReference"));
};

#endif
