#include "bla/bla.hpp"
using namespace ngbla;

#include <math.h>
#include <fstream>
#include <iostream>
/*
a__________________________________________________b__________________________________________________c
Dirichletrand_____x0 ......................xn/2-1_____xn/2+1.....................xn-1_____Dirichletrand für n gerade
Dirichletrand_____x0.............x(n-1)/2-1_____x(n-1)/2_____x(n+1)/2............xn-1_____Dirichletrand für n ungerade
*/

int main(){
  int writeout_stepsize = 1;
  double k1 = 10.;
  double k2 = 1.;
  double a = 0.;
  double b = 0.5;
  double c = 1.;
  
  double u0=0.; //Dirichlet Randbedingung
  double u1=1.; //Dirichlet Randbedingung
  double tmp;
  
  int N = 100; //Anzahl der Stützstellen
  int I = N - 1; //Anzahl der Intervalle
  int n = I - 1; //Anzahl der inneren Stützstelen, also unbekannten == Matrixdimension
  double h = (c-a)/(I);
  ofstream out("heateqn.txt");

  Vector<double> rhs(n);
  Vector<double> u(n);
  
  Matrix<double> A(n);
  Matrix<double> A_inv(n);
  
  rhs = 1.;
  rhs(0) += pow(h,-2)*u0;
  rhs(n-1) += pow(h,-2)*u1;
  
  A=0.;
  for(int i=0;i<n/2;i++){
      A(i+1,i) = -k1;
      A(i,i) = 2*k1;
      A(i,i+1) = -k1;
    }

  
  for(int i=n/2+1;i<n;i++){
      A(i,i-1) = -k2;
      A(i,i) = 2*k2;
      A(i-1,i) = -k2;
    }
  
  if(n%2){ // n%2==1 wahr also n ungerade
    A(n/2,n/2) = k1+k2; // n/2 wird abgerundet
  }
  else{ // also n gerade, achtung n/2-1 ist der mittlere eintrag, weil miss by one
    A(n/2-1,n/2-1) = 3./2*k1 + k2/2;
    A(n/2-1,n/2) = -k1/2 - k2/2;
    A(n/2,n/2-1) = -k1/2 - k2/2;
    A(n/2,n/2) = k1/2 + 3./2*k2;
  }

  
  CalcInverse(A,A_inv);
  u = pow(h,2)*A_inv*rhs;
  /*cout << A << endl;
    cout << endl << A_inv << endl;
    cout << endl << rhs << endl;
    cout << endl << u << endl;
  */
  out << a << " " << u0 << " " << k1*(u0-u(0))/h << "\n";
  for(int i = 0; i<n; i++)
    {
      out << a+(i+1)*h << " " << u(i);
      if (i==n-1)
	out << " " << k2*(u(i)-u1)/h << "\n";
      else
	{
	  if(i<n/2)
	    out << " " << k1*(u(i)-u(i+1))/h << "\n";
	  else
	    out << " " << k2*(u(i)-u(i+1))/h << "\n";
	}
    }
  out << c << " " << u1 << " " << k2*(u(n-1)-u1)/h << endl;
  
  return 0;
}
