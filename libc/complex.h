#ifndef __complex_h_2018_05_08_12_19
#define __complex_h_2018_05_08_12_19

#define imaginary _Imaginary
#define complex _Complex

#pragma macros import("I_val") define("I_val",type)

#pragma macros deduceType("I",type) from(float _Imaginary,double _Imaginary,long double _Imaginary) default(double _Imaginary)\
	define("I") I_val(type)

#define _Imaginary_I I_val(float _Imaginary)
#define _Complex_I 0.0f+I

float complex CMPLXF(float,float);
double complex CMPLX(double,double);
long double complex CMPLXL(long double,long double);

float cimagf(float complex);
double cimag(double complex);
long double cimagl(long double complex);

float crealf(float complex);
double creal(double complex);
long double creall(long double complex);

float complex cprojf(float complex);
double complex cproj(double complex);
long double complex cprojl(long double complex);



#endif
