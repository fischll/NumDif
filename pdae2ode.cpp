#include "bla/bla.hpp"
using namespace ngbla;
#include "ode.hpp"
#include "RK_orig.hpp"
#include <math.h>


class Pendulum_DAE2ODE_Function : public ODE_Function
{
	double g; //gravitation force
	double l; //pendulum länge
        double m;
        mutable double np2;
        mutable double nq2;
public:
  Pendulum_DAE2ODE_Function(double ag, double al, double am) { g = ag; l = al; m = am;}

	//alpha, omega
	virtual void Eval(double t, const Vector<> & y, Vector<> & f) const
	{
	  nq2 = (y(2)*y(2)+y(3)*y(3)); //Norm q hoch 2
	  np2 = (y(0)*y(0)+y(1)*y(1)); //Norm p hoch 2
	  
	  f(0) = m*g*y(2)*y(3)/nq2 -  np2*y(2)/m/nq2;
	  f(1) = m*g*y(3)*y(3)/nq2 -  np2*y(3)/m/nq2 - m*g;
	  f(2) = y(0)/m;
       	  f(3) = y(1)/m;
	}
};



int main()
{
	Classical_expl_RK classic_rk;
	double h = 0.01;

	ofstream out("PenDAE2ODE.txt");
	Pendulum_DAE2ODE_Function pen(1, 1, 1);
	Vector<> y0(4);
	y0=0;
	y0(2) = 1; // startwert mit geschw=0 und ort (x,y)=(1,1)
	y0(3) = 0; //
	ODESolver(pen, classic_rk, 0, y0, 100, h, out, 1);
	return 0;
}
