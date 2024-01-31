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

Complex Complex::operator+(Complex z) {
  return Complex(real + z.real, imag + z.imag);}
  
Complex Complex::operator+(const double val) {
  return Complex(real + val, imag);}

Complex Complex::operator-(Complex z) {
  return Complex(real - z.real, imag - z.imag);}
  
Complex Complex::operator-(const double val) {
  return Complex(real - val, imag);}
  
Complex Complex::operator*(Complex z) {
  return Complex(real * z.real - imag * z.imag, 
    real * z.imag + imag * z.real);}

Complex Complex::operator*(const double val) {
  return Complex(real * val, imag * val);}

Complex Complex::operator/(Complex z) {
  return Complex((real * z.real + imag * z.imag) 
    / (z.real * z.real + z.imag * z.imag), (imag * z.real
    - real * z.imag) / (z.real * z.real + z.imag * z.imag));}
  
Complex Complex::operator/(const double val) {
  return Complex((double)real / val, (double)imag / val);}
    
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
