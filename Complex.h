#include <fstream>
#pragma once
using namespace std;

class Complex {
  public:
    double real;
    double imag;
    
    Complex();
    Complex(double re, double im);
    
    static Complex Rect(double re, double im);
    static Complex Polar(double r, double theta);
    
    void print(); 
    void write(ofstream &fout);
    static double mod(Complex z);   
    static double arg(Complex z); 
    static Complex add(Complex z1, Complex z2);     
    static Complex add(Complex z, const double val);    
    static Complex multiply(Complex z1, Complex z2);
    static Complex multiply(Complex z, const double val);  
    static Complex divide(Complex z1, Complex z2);
    static Complex divide(Complex z, const double val);   
    static Complex square(Complex z);
    static Complex csqrt(Complex z);
    static Complex cexp(Complex z);
};
