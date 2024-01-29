#include <fstream>
#include <vector>
#include "Complex.h"
#pragma once
using namespace std;

class ComplexMatrix {
  public:
    int length;
    
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
    static ComplexMatrix slice(const int lower_bound, const int upper_bound, ComplexMatrix a);
    static ComplexMatrix add(ComplexMatrix a, ComplexMatrix b);
    static ComplexMatrix add(ComplexMatrix a, Complex z);
    static ComplexMatrix add(ComplexMatrix a, const double val);
    static ComplexMatrix multiply(ComplexMatrix a, ComplexMatrix b);
    static ComplexMatrix multiply(ComplexMatrix a, Complex z);
    static ComplexMatrix multiply(ComplexMatrix a, const double val);
    static ComplexMatrix divide(ComplexMatrix a, ComplexMatrix b);
    static ComplexMatrix divide(ComplexMatrix a, Complex z);
    static ComplexMatrix divide(ComplexMatrix a, const double val);
    static ComplexMatrix square(ComplexMatrix a);
    static ComplexMatrix csqrt(ComplexMatrix a);
    static ComplexMatrix cexp(ComplexMatrix a);
  
  private:
    vector<Complex> array;
};
