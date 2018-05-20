#include "bla/bla.hpp"
using namespace ngbla;

#include <math.h>
#include <fstream>
#include <iostream>

int main(){
  int writeout_stepsize = 1;
  int n = 99; //gerade
  double k1 = 10.;
  double k2 = 1.;
  double a = 0.;
  double b = 0.5;
  double c = 1.;
  double u0=0.;
  double u1=1.;
  double tmp;

  double h = (c-a)/(n+1);
  ofstream out("heateqn.txt");

  Vector<> rs(n);
  Vector<double> u(n);
  
  Matrix<> A(n);
  Matrix<> A_inv(n);
  
  rs = 1./k2;
  for(int i=0; i<n/2; i++)
    {
      rs(i)=1./k1;
      //rs(i+n/2)=-1./k2;
    }

  rs(0) += pow(h,-2)*u0;
  rs(n-1) += pow(h,-2)*u1;
  
  A=0.;
  
  for(int i=0;i<n;i++)
    {
      A(i,i-1) = -1;
      A(i,i) = 2;
      A(i,i+1) = -1;
    }

    CalcInverse(A,A_inv);
    u = pow(h,2)*A_inv*rs;
    /* cout << A << endl;
    cout << endl << A_inv << endl;
    cout << endl << rs << endl;
    cout << endl << u << endl;
    */
    out << a << " " << u0 << "\n";
    for(int i = 0; i<n; i++)
      {
	tmp = u(i);
	out << a+(i+1)*h << " " << tmp << "\n";
      }
    out << c << " " << u1 << "\n";
    return 0;
    
}
