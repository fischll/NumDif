#include "bla/bla.hpp"
using namespace ngbla;

#include <math.h>
#include <fstream>
#include <iostream>

int main(){
  int writeout_stepsize = 1;
  int p = 32; //Anzahl der Stützstellen == höchster Polynomgrad-1 == Anzahl der Basisfunktionen x^i
  int I = p-1; //Anzahl der Intervalle
  //seien {u0,..up-1} die Koeffizeinten der Basispolynome(=Monome) also Polynomkoeffizienten dann ist u0 bereits bekannt, da dort Dirichlet Randbedingungen
  //Somit bleiben (p-1) koeffizienten über
  double a = 0.;
  double b = 1.;
  
  double u0 = 0.; //Dirichlet Randbedingung
  double u_strich_1 = 1.; //Dirichlet Randbedingung
  double tmp;

  double h = (b-a)/I;
  ofstream out("monombasis.txt");

  Vector<double> rhs(p);
  Vector<double> u(p);
  
  Matrix<double> A(p);
  Matrix<double> A_inv(p);

  for(int j=0;j<p;j++){
    rhs(j) = 1./(j+1)-u_strich_1;
  }
  
  A=0.;
  for(int i=0;i<p;i++){
    for(int j=0;j<p;j++){
      if(i==0||j==0){
	if(i==0&&j==0)
	  A(i,j)=1;
	else
	  A(i,j)=0;
      }
      else{
	A(i,j) = 1./(i*j+1) + double(i*j)/((i-1)*(j-1)+1);
      }
    }
  }
  
  CalcInverse(A,A_inv);
  u = A_inv*rhs;
  /*cout << A << endl;
    cout << endl << A_inv << endl;
    cout << endl << rhs << endl;*/
    cout << endl << A << endl;
    cout << endl << u << endl;
  

  //out << xWert << " " << yWert << " " << Energie << endl;
    out << a << " " << u0 << " " << u0 << "\n";
  for(int i = 0; i<p; i++)
    {
      tmp = 0.;
      for(int j=0;j<p;j++){
	tmp += u(j) * pow(a + i*h, j);
      }
      out << a + i*h << " " << tmp ;
      tmp = a + i*h;
      out << " " << (exp(2-tmp) - exp(tmp)+1 - exp(2))/(1-exp(2));
      out << "\n";
    }
  
  return 0;
}
