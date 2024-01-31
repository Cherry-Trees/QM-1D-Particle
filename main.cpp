#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include "Complex.h"
#include "ComplexMatrix.h"
using namespace cmatrix;

// Return the normalized wave function
ComplexMatrix normalize(ComplexMatrix waveFuncImage, double dx) {
  Complex norm = ComplexMatrix::sum(ComplexMatrix::square(ComplexMatrix::mod(waveFuncImage))) * dx;
  return waveFuncImage / Complex::csqrt(norm);
}

// Return an image of the initial wave function
ComplexMatrix waveFunc(ComplexMatrix x, double p, double mu, double sigma, double dx) {
  ComplexMatrix probability = ComplexMatrix::cexp(ComplexMatrix::square(x - mu) / (-2 * (sigma * sigma)));
  ComplexMatrix momentum = ComplexMatrix::cexp(x * Complex::Rect(0, p));
  return normalize(probability * momentum, dx);
}

// Return the squared gradient of the wave function
ComplexMatrix discreteLaplace(ComplexMatrix waveFuncImage) {
  ComplexMatrix diff = ComplexMatrix::Zeros(waveFuncImage.length);
  diff.equals(1, diff.length-1, waveFuncImage.slice(2, waveFuncImage.length) + 
    waveFuncImage.slice(0, waveFuncImage.length-2) + waveFuncImage.slice(1, waveFuncImage.length-1) * -2);
  return diff;
}

// Return the Schrodinger equation solved for the first time derivative of psi
ComplexMatrix schrodinger(ComplexMatrix waveFuncImage, double hbar, double m, ComplexMatrix potentialFuncImage) {
  ComplexMatrix dpsidt = discreteLaplace(waveFuncImage) * Complex::Rect(0, hbar / 2 * m) - 
    potentialFuncImage * Complex::Rect(0, 1) * waveFuncImage;
  return dpsidt;
}

// Potential function
ComplexMatrix potential(ComplexMatrix x) {
  return ComplexMatrix::square(x) * 2;
  //return ComplexMatrix::Zeros(x.length);
}

// Integrate the Schrodinger equation with respect to time
ComplexMatrix rk4_iter(ComplexMatrix (*f)(ComplexMatrix, double, double, ComplexMatrix), 
  ComplexMatrix waveFuncImage, double dt, double hbar, double m, ComplexMatrix potentialFuncImage) {
  ComplexMatrix k1 = f(waveFuncImage, hbar, m, potentialFuncImage) * dt;
  ComplexMatrix k2 = f(waveFuncImage + k1 * 0.5, hbar, m, potentialFuncImage) * dt;
  ComplexMatrix k3 = f(waveFuncImage + k2 * 0.5, hbar, m, potentialFuncImage) * dt;
  ComplexMatrix k4 = f(waveFuncImage + k3, hbar, m, potentialFuncImage) * dt;
  return waveFuncImage + ((k1 + k2 * 2 + k3 * 2 + k4) * (double)1/6);
}

int main() {

  // Create a discrete domain image of x
  const double dx = 0.01;
  const int n = 1000;
  vector<Complex> x;
  for (int i=-n/2; i<n/2; i++) {
    x.push_back(Complex::Rect((double)i*dx, 0));
  }

  // Initial conditions and properties
  const double m = 20;
  const double hbar = 1;
  const double mu = 0;
  const double p = 20;
  const double sigma = 0.2;
  
  // Construct complex matrices
  ComplexMatrix X(x);
  ComplexMatrix V = potential(X);
  ComplexMatrix psi = waveFunc(X, p, mu, sigma, dx);

  const double dt = 0.025;
  const double steps = 3000;
  
  ofstream fout;
  fout.open("particledata.txt");
  fout << dt << endl;
  fout << steps << endl;
  fout << dx << endl;
  fout << n << endl;
  
  // Integrate psi over the time interval
  for (int i=0; i<steps; i++) {
    psi.write(fout);
    fout << endl << "break" << endl;
    psi.equals(rk4_iter(&schrodinger, psi, dt, hbar, m, V));
    psi.equals(normalize(psi, dx)); 
  }
  
  fout.close();
  return 0;
}
