#include "bla/bla.hpp"
using namespace ngbla;

#include <math.h>
#include <fstream>
#include <iostream>

int main(){
  int writeout_stepsize = 1;
  int n = 98; //gerade
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

  Vector<double> rs(n);
  Vector<double> u(n);
  
  Matrix<double> A(n);
  Matrix<double> A_inv(n);
  
  rs = 1./k2;
  for(int i=0; i<n/2; i++)
    {
      rs(i)=1./k1;
      //rs(i+n/2)=-1./k2;
    }

  rs(0) += pow(h,-2)*u0;
  rs(n-1) += pow(h,-2)*u1;
  
  A=0.;
  
  for(int i=0;i<n-1;i++)
    {
      A(i+1,i) = -1.;
      A(i,i) = 2.;
      A(i,i+1) = -1.;
    }
  A(n-1,n-1)=2.;
  
  CalcInverse(A,A_inv);
    u = pow(h,2)*A_inv*rs;
    /*cout << A << endl;
    cout << endl << A_inv << endl;
    cout << endl << rs << endl;
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
    out << c << " " << u1 <<" " << k2*(u(n-1)-u1)/h << endl;

    return 0;
}
