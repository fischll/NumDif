#include "bla/bla.hpp"
using namespace ngbla;

#include <math.h>
#include <fstream>
#include <iostream>

double eval(Vector<> & coef, int grad, double x){
  double ret = coef(0);
  for(int i = 1; i <= grad; i++)
    ret += coef(i) * pow(x,i);
  return ret;
}


int main(int nargs, char* argv[]){
  istringstream ss(argv[1]);
  int p;
  if (!(ss >> p))
    cerr << "Invalid number " << argv[1] << '\n';
  int n = p+1; //Anzahl der Stützstellen == Anzahl der Basisfunktionen x^i
  int I = p; //Anzahl der Intervalle
  //seien {u0,..up==un-1} die Koeffizeinten der Basispolynome(=Monome) also Polynomkoeffizienten
  //dann ist u0 bereits bekannt, da dort Dirichlet Randbedingungen
  //Somit bleiben p koeffizienten über
  double a = 0.;
  double b = 1.;
  
  double u0 = 0.; //Dirichlet Randbedingung
  double u_strich_1 = 1.; //Neumann Randbedingung
  ofstream out("monombasis.txt");

  Vector<double> rhs(p);
  Vector<double> u(p+1);
  
  Matrix<double> A(p);
  Matrix<double> A_inv(p);
  rhs = 0.;
  u=0.;
  for(int j=0;j<p;j++)
    rhs(j) = 1./(j+2) + u_strich_1;
  
  A=0.;
  for(int i=1;i<p+1;i++)
    for(int j=1;j<p+1;j++)
      A(i-1,j-1) = 1./(i+j+1) + ((double)i*j)/((i-1)+(j-1)+1);
  
  CalcInverse(A,A_inv);
  u.Range(1,p+1) = A_inv*rhs;

  //out << xWert << " " << yWert << " " << Energie << endl;
  // out << a << " " << u0 << " " << u0 << "\n;"
  for(double x = 0; x<1; x+=0.05){ 
    out << x << " " << eval(u,p,x) ;
    out << " " << (-exp(1-x) - exp(2-x) - exp(x) + exp(x+1) + 1 + exp(2))/(exp(2)+1);
    out << "\n";
  }
  
  return 0;
}

