#include <fstream>
#include <vector>
#include "Complex.h"
#pragma once

namespace cmatrix {
  class ComplexMatrix;
}

class cmatrix::ComplexMatrix {
  public:
    int length;
    vector<Complex> array;
    
    ComplexMatrix(const vector<Complex> &init_array);
    static ComplexMatrix Zeros(const int array_length);
    
    void print();
    void write(ofstream &fout);
    void equals(const int lower_bound, const int upper_bound, ComplexMatrix m);  
    void equals(ComplexMatrix m);
    void equals(const int lower_bound, const int upper_bound, Complex z);
    void equals(Complex z);  
    
    static Complex sum(ComplexMatrix a); 
    static ComplexMatrix mod(ComplexMatrix a);
    ComplexMatrix slice(const int lower_bound, const int upper_bound);
    ComplexMatrix operator+(ComplexMatrix b);
    ComplexMatrix operator+(Complex z);
    ComplexMatrix operator+(const double val);
    ComplexMatrix operator-(ComplexMatrix b);
    ComplexMatrix operator-(Complex z);
    ComplexMatrix operator-(const double val);
    ComplexMatrix operator*(ComplexMatrix b);
    ComplexMatrix operator*(Complex z);
    ComplexMatrix operator*(const double val);
    ComplexMatrix operator/(ComplexMatrix b);
    ComplexMatrix operator/(Complex z);
    ComplexMatrix operator/(const double val);
    static ComplexMatrix square(ComplexMatrix a);
    static ComplexMatrix csqrt(ComplexMatrix a);
    static ComplexMatrix cexp(ComplexMatrix a);
};
