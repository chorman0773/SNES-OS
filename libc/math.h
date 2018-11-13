#ifndef __math_h_2018_04_20_12_55
#define __math_h_2018_04_20_12_55


#ifdef __cplusplus
extern "C"{
#endif
#define HUGE_VAL (double)__builtin_infinity()
#define HUGE_VALF (float)__builtin_infinity()
#define HUGE_VALL (long double)__builtin_infinity()

#define INFINITY __builtin_infinity()

#pragma macros hide(1)
#define __builtin_overload(name,...) double name(double);
#pragma macros hide(0)

#define __mathdef1(name)\
	double __##name(double);\
	float name##f(float);\
	long double name##l(long double);\
	__builtin_overload(name,double,__##name,float,name##f,long double,name##l)

#define __mathdef2(name)\
	double __##name(double,double);\
	float name##f(float,float);\
	long double name##l(long double,long double);\
	__builtin_overload(name,double,__##name,float,name##f,long double,name##l)

/**
double acos(double);
double asin(double);
double atan(double);
double atan2(double,double);

double cos(double);
double sin(double);
double tan(double);

double cosh(double);
double sinh(double);
double tanh(double);

double exp(double);
double pow(double,double);
double sqrt(double);

double log(double);
double log10(double);

double fabs(double);
double ceil(double);
double floor(double);
*/

__mathdef1(acos);
__mathdef1(asin);
__mathdef1(atan);
__mathdef2(atan2);
__mathdef1(cos);
__mathdef1(sin);
__mathdef1(tan);
__mathdef1(cosh);
__mathdef1(sinh);
__mathdef1(tanh);
__mathdef1(exp);
__mathdef1(sqrt);
__mathdef2(pow);
__mathdef1(log);
__mathdef1(log10);
__mathdef1(fabs);
__mathdef1(ceil);
__mathdef1(floor);

#define NAN __builtin_nan("");

#define nan(str) (double)__builtin_nan(str)
#define nanf(str) (float)__builtin_nan(str)
#define nanl(str) (long double)__builtin_nan(str)


#ifdef __cplusplus
};
#endif
#endif
