#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include "Complex.h"
#include "ComplexMatrix.h"
using namespace std;

// Return the normalized wave function
ComplexMatrix normalize(ComplexMatrix waveFuncImage, double dx) {
  Complex norm = Complex::multiply(ComplexMatrix::sum(ComplexMatrix::square(ComplexMatrix::mod(waveFuncImage))), dx);
  return ComplexMatrix::divide(waveFuncImage, Complex::csqrt(norm));
}

// Return an image of the initial wave function
ComplexMatrix waveFunc(ComplexMatrix x, double p, double mu, double sigma, double dx) {
  ComplexMatrix probability = ComplexMatrix::cexp(ComplexMatrix::divide(ComplexMatrix::square(ComplexMatrix::add(x, -mu)), -2 * (sigma * sigma)));
  ComplexMatrix momentum = ComplexMatrix::cexp(ComplexMatrix::multiply(x, Complex::Rect(0, p)));
  return normalize(ComplexMatrix::multiply(probability, momentum), dx);
}

// Return the squared gradient of the wave function
ComplexMatrix discreteLaplace(ComplexMatrix waveFuncImage) {
  ComplexMatrix diff = ComplexMatrix::Zeros(waveFuncImage.length);
  diff.equals(1, diff.length-1, ComplexMatrix::add(ComplexMatrix::add(ComplexMatrix::slice(2, waveFuncImage.length, waveFuncImage), 
    ComplexMatrix::slice(0, waveFuncImage.length-2, waveFuncImage)), ComplexMatrix::multiply(ComplexMatrix::slice(1, waveFuncImage.length-1, waveFuncImage), -2)));
  return diff;
}

// Return the Schrodinger equation solved for the first time derivative of psi
ComplexMatrix schrodinger(ComplexMatrix waveFuncImage, double hbar, double m, ComplexMatrix potentialFuncImage) {
  ComplexMatrix dpsidt = ComplexMatrix::add(ComplexMatrix::multiply(discreteLaplace(waveFuncImage), Complex::Rect(0, hbar / 2 * m)), 
    ComplexMatrix::multiply(ComplexMatrix::multiply(potentialFuncImage, Complex::Rect(0, -1)), waveFuncImage));
  return dpsidt;
}

// Potential function
ComplexMatrix potential(ComplexMatrix x) {
  //return ComplexMatrix::multiply(ComplexMatrix::square(x), 0.5);
  return ComplexMatrix::Zeros(x.length);
}

// Integrate the Schrodinger equation with respect to time
ComplexMatrix rk4_iter(ComplexMatrix (*f)(ComplexMatrix, double, double, ComplexMatrix), 
  ComplexMatrix waveFuncImage, double dt, double hbar, double m, ComplexMatrix potentialFuncImage)
{
  ComplexMatrix k1 = ComplexMatrix::multiply(f(waveFuncImage, hbar, m, potentialFuncImage), dt);
  ComplexMatrix k2 = ComplexMatrix::multiply(f(ComplexMatrix::add(waveFuncImage, ComplexMatrix::multiply(k1, 0.5)), 
    hbar, m, potentialFuncImage), dt);
  ComplexMatrix k3 = ComplexMatrix::multiply(f(ComplexMatrix::add(waveFuncImage, ComplexMatrix::multiply(k2, 0.5)), 
    hbar, m, potentialFuncImage), dt);
  ComplexMatrix k4 = ComplexMatrix::multiply(f(ComplexMatrix::add(waveFuncImage, k3), hbar, m, potentialFuncImage), dt);
  return ComplexMatrix::add(waveFuncImage, ComplexMatrix::multiply(ComplexMatrix::add(ComplexMatrix::add(k1, ComplexMatrix::multiply(k2, 2)), 
    ComplexMatrix::add(ComplexMatrix::multiply(k3, 2), k4)), (double)1/6));
}

int main() {

  // Create a discrete domain image of x
  const double dx = 0.01;
  vector<Complex> x;
  for (int i=-1000; i<1000; i++) {
    x.push_back(Complex::Rect((double)i*dx, 0));
  }

  // Initial conditions and properties
  const double m = 30;
  const double hbar = 1;
  const double mu = 0;
  const double p = 10/3;
  const double sigma = 2;
  
  // Construct complex matrices
  ComplexMatrix X(x);
  ComplexMatrix V = potential(X);
  ComplexMatrix psi = waveFunc(X, p, mu, sigma, dx);

  const double dt = 0.01;
  const double steps = 1000;
  
  ofstream fout;
  fout.open("particledata.txt");
  
  // Integrate psi over the time interval
  for (int i=0; i<steps; i++) {
    psi.equals(rk4_iter(&schrodinger, psi, dt, hbar, m, V));
    psi.equals(normalize(psi, dx)); 
  }
  
  psi.write(fout);
  fout.close();
  return 0;
}
