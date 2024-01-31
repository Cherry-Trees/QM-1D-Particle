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
    Complex operator+(Complex z);
    Complex operator+(const double val);  
    Complex operator-(Complex z);
    Complex operator-(const double val);   
    Complex operator*(Complex z);
    Complex operator*(const double val);  
    Complex operator/(Complex z);
    Complex operator/(const double val);   
    static Complex square(Complex z);
    static Complex csqrt(Complex z);
    static Complex cexp(Complex z);
};
