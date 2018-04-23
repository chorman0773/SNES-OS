#ifndef __math_h_2018_04_20_12_55
#define __math_h_2018_04_20_12_55

extern const double _huge_val_value;
#ifdef __cplusplus
extern "C"{
#endif
#define HUGE_VAL _huge_val_value
    
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
double sqrt(double,double);

double log(double);
double log10(double);

double fabs(double);
double ceil(double);
double floor(double);


#ifdef __cplusplus
};
#endif
#endif
