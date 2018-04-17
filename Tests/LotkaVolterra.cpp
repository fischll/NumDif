#include "bla/bla.hpp"
using namespace ngbla;
#include "ode.hpp"
#include "RK_orig.hpp"
#include <math.h>

class Circuid_ODE_Function : public ODE_Function
{
	double b; // Beute
	double r; // Räuber
	double epsilon; 

public:
	LotkaVolterra_ODE_Function(double rm, double bm) {
		r = rm;
		b = bm;
	}

	virtual void Eval(double t, const Vector<> & y, Vector<> & f) const
	{
		f(0) = ;
		f(1) = ;
	}
};


int main()
{
	ImplicitEuler impl_euler;
	//ExplicitEuler expl_euler;
	Vector<> c = { 0.001,0.001 };
	Vector<> r = { 1000,1 };
	double omega = 1000;
	double h = 0.0001;
	double t0 = 0.;
	double T = 2;
	int stepsave = 1;

	ofstream out("circuit.out");
	Circuid_ODE_Function circuit(c, r, omega);
	Vector<> y0(2);
	y0 = 0.;

	ODESolver(circuit, impl_euler, t0, y0, T, h, out, stepsave);
	//ODESolver(circuit, expl_euler, t0, y0, T, h, out, stepsave);

	return 0;
}
