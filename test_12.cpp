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
		f(1) = -(g / l) * sin(y(0));
	}
};


int main()
{
	Bsp16 imprEV;
	Gauss2 gauss2;

	cout << 0 << endl << 0. << endl << 0.0 << 1. / 2 << endl;
	double h = 0.001;
	double t0 = 0.;
	double T = 10;
	int stepsave = 1;

	ofstream out_implMP("Pen_imprEV.out");
	ofstream out_gauss2("Pen_gauss2.out");

	Pendulum_ODE_Function pen(1, 1);
	Vector<> y0(2);
	y0(0) = M_PI / 2; //das ist ja nur ein startwert und pi ging nicht
	y0(1) = 0;

	ODESolver(pen,  imprEV, t0, y0, T, h, out_implMP, stepsave);
	ODESolver(pen, gauss2, t0, y0, T, h, out_gauss2, stepsave);

	return 0;
}
