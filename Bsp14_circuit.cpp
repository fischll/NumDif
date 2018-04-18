#include "bla/bla.hpp"
using namespace ngbla;
#include "ode.hpp"
#include "RK_orig.hpp"
#include <math.h>

class Circuid_ODE_Function : public ODE_Function
{
	Vector<> c; //Kapazität 
	Vector<> r; //Wiederstand
	double omega;

public:
	Circuid_ODE_Function(Vector<> & cm, Vector<> & rm, double omegam) {
		c.SetSize(2);
		r.SetSize(2);
		c(0) = cm(0);
		c(1) = cm(1);
		r(0) = rm(0);
		r(1) = rm(1);
		omega = omegam;
	}

	virtual void Eval(double t, const Vector<> & y, Vector<> & f) const
	{
		f(0) = (sin(omega*t) - y(0)) / c(0) / r(0) - (y(0) - y(1)) / c(0) / r(1);
		f(1) = (y(0) - y(1)) / c(1) / r(1);
	}
};


int main()
{
	ImplicitEuler impl_euler;
	ExplicitEuler expl_euler;
	ImplMP impl_MP;
	Bsp16 bsp16;

	Vector<> c = { 0.001,0.001 };
	Vector<> r = { 1000,1 };
	double omega = 1;
	double h = 1e-1;
	double t0 = 0.;
	double T = 100;
	int stepsave = 1;

	ofstream out_impl_MP("circuit_impl_MP.out");
	//ofstream out_expl_EV("circuit_expl_EV.out");
	ofstream out_impl_EV("circuit_impl_EV.out");
	ofstream out_bsp16("circuit_bsp16.out");	

	Circuid_ODE_Function circuit(c, r, omega);
	Vector<> y0(2);
	y0(0) = -1;
	y0(1) = 1;

	ODESolver(circuit, impl_euler, t0, y0, T, h, out_impl_EV, stepsave);
	//ODESolver(circuit, expl_euler, t0, y0, T, h, out_expl_EV, stepsave);
	ODESolver(circuit, impl_MP, t0, y0, T, h, out_impl_MP, stepsave);
	ODESolver(circuit, bsp16, t0, y0, T, h, out_bsp16, stepsave);
	return 0;
}