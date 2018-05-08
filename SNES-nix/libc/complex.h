#ifndef __complex_h_2018_05_08_12_19
#define __complex_h_2018_05_08_12_19

#define imaginary _Imaginary
#define complex _Complex

#pragma macros import(macro,"I_val") define(I_val(type))

#pragma macros deduceType(I_val,type) from(float _Imaginary,double _Imaginary,long double _Imaginary default double _Imaginary)\
	define I I_val(type)

#define _Imaginary_I I_val(float _Imaginary)
#define _Complex_I 0.0f+I

#define CMPLX(r,i) (double complex)(((double)r)+((double)i)*I)
#define CMPLXF(r,i) (float complex)(((float)r)+((float)i)*I)


#endif
