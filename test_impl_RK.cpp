#include "bla/bla.hpp"
using namespace ngbla;
#include "ode.hpp"
#include "RK_orig.hpp"
#include <math.h>


class E_ODE_Function : public ODE_Function
{
public:
	E_ODE_Function() {  }

	virtual void Eval(double t, const Vector<> & y, Vector<> & f) const
	{
		f(0) = y(0);
	}
};


int main()
{
	ExplicitEuler expl_euler;
	ImplMP impl_MP;
	Gauss2 gauss2;

	double h = 0.2;
	double t0 = 0.;
	double T = 2;
	int stepsave = 1;

	ofstream out_implMP("EFunc_implMP.out");
	ofstream out_explEV("EFunc_explEV.out");
	ofstream out_gauss2("EFunc_gauss2.out");
	E_ODE_Function	efunc;
	Vector<> y0 = { 1. };

	ODESolver(efunc, impl_MP, t0, y0, T, h, out_implMP, stepsave);
	ODESolver(efunc, expl_euler, t0, y0, T, h, out_explEV, stepsave);
	ODESolver(efunc, gauss2, t0, y0, T, h, out_gauss2, stepsave);

	return 0;
}
