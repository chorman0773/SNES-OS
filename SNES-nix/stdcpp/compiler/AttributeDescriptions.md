This file describes all the attributes provided by the SNES-OS C++ compiler that are for use in the stdc++ headers.
These attributes are accessible via `__attribute((stdcpp_attr_<name>)) (deprecated)` or `[[stdcpp::<name>]]`
Note that using `__attribute((<attribute>))` will point you to using `[[<attribute>]]` instead in the C++ compiler.

#Attributes

##optimization_candidate
This attribute is used to denote a stdc++ function that is a candidate for optimization. That is, the compiler can optimize 
its usage of the function at compile time, even if its not a constexpr function.
This attribute is only a hint, and may be ignored. The compiler will always optimize its useage in unevaluated contexts.

##no_odr
Indicates that the given function is not legal in an evaluated context, and its use in such a context is a compile error.
An example of `[[stdcpp::no_odr]]` is declval. In addition, the compiler will warn if a no_odr function is defined.
This has the side effect of making it easier to detect usage of certain functions (as such is a compile error, instead of a linkage error).
