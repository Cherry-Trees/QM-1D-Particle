#include <iostream>
#include <fstream>
#include <vector>
#include "Complex.h"
#include "ComplexMatrix.h"
using namespace std;

ComplexMatrix::ComplexMatrix(const vector<Complex> &init_array) {
  length = init_array.size();
  for (int i=0; i<length; i++) {array.push_back(init_array[i]);} 
}

ComplexMatrix ComplexMatrix::Zeros(const int array_length) {
    vector<Complex> v;
    for (int i=0; i<array_length; i++) {v.push_back(Complex(0, 0));}
    return ComplexMatrix(v);
}

void ComplexMatrix::print() {
  for (Complex z : array) {z.print();}
}

void ComplexMatrix::write(ofstream &fout) {
  for (Complex z : array) {z.write(fout);}
}

void ComplexMatrix::equals(const int lower_bound, const int upper_bound, ComplexMatrix m) {
  for (int i=lower_bound; i<upper_bound; i++) {
    array[i] = m.array[i-lower_bound];}
  return;
}

void ComplexMatrix::equals(ComplexMatrix m) {
  for (int i=0; i<length; i++) {array[i] = m.array[i];}
  return;
}

void ComplexMatrix::equals(const int lower_bound, const int upper_bound, Complex z) {
  for (int i=lower_bound; i<upper_bound; i++) {array[i] = z;}
  return;
}

void ComplexMatrix::equals(Complex z) {
  for (int i=0; i<length; i++) {array[i] = z;}
  return;
}

Complex ComplexMatrix::sum(ComplexMatrix a) {
  Complex sum;
  for (int i=0; i<a.length; i++) {
    sum = Complex::add(sum, a.array[i]);}
  return sum;
}

ComplexMatrix ComplexMatrix::slice(const int lower_bound, const int upper_bound, ComplexMatrix a) {
  vector<Complex> v;
  for (int i=lower_bound; i<upper_bound; i++) {v.push_back(a.array[i]);}
  return ComplexMatrix(v);
}

ComplexMatrix ComplexMatrix::mod(ComplexMatrix a) {
  vector<Complex> v;
  for (int i=0; i<a.length; i++) {
    v.push_back(Complex(Complex::mod(a.array[i]), 0));}
  return v;
}

ComplexMatrix ComplexMatrix::add(ComplexMatrix a, ComplexMatrix b) {
  vector<Complex> v;
  for (int i=0; i<a.length; i++) {
    v.push_back(Complex::add(a.array[i], b.array[i]));}
  return ComplexMatrix(v);
}
  
ComplexMatrix ComplexMatrix::add(ComplexMatrix a, Complex z) {
  vector<Complex> v;
  for (int i=0; i<a.length; i++) {
    v.push_back(Complex::add(a.array[i], z));}
  return ComplexMatrix(v);
}

ComplexMatrix ComplexMatrix::add(ComplexMatrix a, const double val) {
  vector<Complex> v;
  for (int i=0; i<a.length; i++) {
    v.push_back(Complex::add(a.array[i], val));}
  return ComplexMatrix(v);
}

ComplexMatrix ComplexMatrix::multiply(ComplexMatrix a, ComplexMatrix b) {
  vector<Complex> v;
  for (int i=0; i<a.length; i++) {
    v.push_back(Complex::multiply(a.array[i], b.array[i]));}
  return ComplexMatrix(v);
}

ComplexMatrix ComplexMatrix::multiply(ComplexMatrix a, Complex z) {
  vector<Complex> v;
  for (int i=0; i<a.length; i++) {
    v.push_back(Complex::multiply(a.array[i], z));}
  return ComplexMatrix(v);
}

ComplexMatrix ComplexMatrix::multiply(ComplexMatrix a, const double val) {
  vector<Complex> v;
  for (int i=0; i<a.length; i++) {
    v.push_back(Complex::multiply(a.array[i], val));}
  return ComplexMatrix(v);
}

ComplexMatrix ComplexMatrix::divide(ComplexMatrix a, ComplexMatrix b) {
  vector<Complex> v;
  for (int i=0; i<a.length; i++) {
    v.push_back(Complex::divide(a.array[i], b.array[i]));}
  return ComplexMatrix(v);
}

ComplexMatrix ComplexMatrix::divide(ComplexMatrix a, Complex z) {
  vector<Complex> v;
  for (int i=0; i<a.length; i++) {
    v.push_back(Complex::divide(a.array[i], z));}
  return ComplexMatrix(v);
}

ComplexMatrix ComplexMatrix::divide(ComplexMatrix a, const double val) {
  vector<Complex> v;
  for (int i=0; i<a.length; i++) {
    v.push_back(Complex::divide(a.array[i], val));}
  return ComplexMatrix(v);
}

ComplexMatrix ComplexMatrix::square(ComplexMatrix a) {
  vector<Complex> v;
  for (int i=0; i<a.length; i++) {
    v.push_back(Complex::square(a.array[i]));}
  return ComplexMatrix(v);
}

ComplexMatrix ComplexMatrix::csqrt(ComplexMatrix a) {
  vector<Complex> v;
  for (int i=0; i<a.length; i++) {
    v.push_back(Complex::csqrt(a.array[i]));}
  return ComplexMatrix(v);
}

ComplexMatrix ComplexMatrix::cexp(ComplexMatrix a) {
  vector<Complex> v;
  for (int i=0; i<a.length; i++) {
    v.push_back(Complex::cexp(a.array[i]));}
  return ComplexMatrix(v);
}
