#include "bla/bla.hpp"
using namespace ngbla;
#include "ode.hpp"
#include "RK_orig.hpp"
#include <math.h>


class Pendulum_ODE_Function : public ODE_Function
{
	double g; //gravitation force
	double l; //pendulum länge
public:
	Pendulum_ODE_Function(double am, double ak) { g = am; l = ak; }

	//alpha, omega
	virtual void Eval(double t, const Vector<> & y, Vector<> & f) const
	{
		f(0) = y(1);
		f(1) = -(g/l) * sin(y(0));
	}
};



int main()
{
	ImplicitEuler impl_euler;
	double h = 0.01;

	ofstream out("Pendulum.txt");
	Pendulum_ODE_Function pen(1, 1);
	Vector<> y0(2);
	y0(0) = M_PI / 2; //das ist ja nur ein startwert und pi ging nicht
	y0(1) = 0;
	ODESolver(pen, impl_euler, 0, y0, 1000, h, out, 10);
	return 0;
}
