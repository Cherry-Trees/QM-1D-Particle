#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
#include "Complex.h"
using namespace std;

Complex::Complex() {real = 0; imag = 0;}
Complex::Complex(double re, double im) {real = re; imag = im;}

Complex Complex::Rect(double re, double im) {
  return Complex(re, im);}
Complex Complex::Polar(double r, double theta) {
  return Complex(r*cos(theta), r*sin(theta));} 

void Complex::print() {
  cout << real << " " << imag << " ";}
  
void Complex::write(ofstream &fout) {
  fout << real << " " << imag << " ";}

double Complex::mod(Complex z) {
  return sqrt((z.real * z.real) + (z.imag * z.imag));}
  
double Complex::arg(Complex z) {
      return atan2(z.imag, z.real);}

Complex Complex::add(Complex z1, Complex z2) {
  return Complex(z1.real + z2.real, z1.imag + z2.imag);}
  
Complex Complex::add(Complex z, const double val) {
  return Complex(z.real + val, z.imag);}
  
Complex Complex::multiply(Complex z1, Complex z2) {
  return Complex(z1.real * z2.real - z1.imag * z2.imag, 
    z1.real * z2.imag + z1.imag * z2.real);}

Complex Complex::multiply(Complex z, const double val) {
  return Complex(z.real * val, z.imag * val);}

Complex Complex::divide(Complex z1, Complex z2) {
  return Complex((z1.real * z2.real + z1.imag * z2.imag) 
    / (z2.real * z2.real + z2.imag * z2.imag), (z1.imag * z2.real
    - z1.real * z2.imag) / (z2.real * z2.real + z2.imag * z2.imag));}
  
Complex Complex::divide(Complex z, const double val) {
  return Complex((double)z.real / val, (double)z.imag / val);}
    
Complex Complex::square(Complex z) {
  return Complex(z.real * z.real - z.imag * z.imag, 2 * z.real * z.imag);}

Complex Complex::csqrt(Complex z) {
  double a, b;
  if (z.imag != 0) {
    a = sqrt((mod(z) + z.real) / 2);
    b = (z.imag / abs(z.imag)) * sqrt((mod(z) - z.real) / 2);
  }
  else {
    a = sqrt(z.real);
    b = 0;
  }
  return Complex(a, b);}

Complex Complex::cexp(Complex z) {return Complex::Polar(exp(z.real), z.imag);}
