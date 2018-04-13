#include "bla/bla.hpp"
using namespace ngbla;
#include "ode.hpp"
#include "RK_orig.hpp"
#include <math.h>


class Dif_ODE_Function : public ODE_Function
{
public:
	Dif_ODE_Function() {  }

	virtual void Eval(double t, const Vector<> & y, Vector<> & f) const
	{
		f(0) = (pow(y(0), 2) - t * y(0)) / (2 * t*pow(y(0), 3) + t * y(0) + pow(t, 2));
	}
};


int main()
{
	ExplicitEuler expl_euler;
	ImplMP impl_MP;
	Gauss2 gauss2;

	double h = 0.0001;
	double t0 = 0.;
	double T = 2;
	int stepsave = 1;

	ofstream out_implMP("DifUE_implMP.out");
	ofstream out_explEV("DifUE_explEV.out");
	ofstream out_gauss2("DifUE_gauss2.out");
	Dif_ODE_Function difue;
	Vector<> y0 = { 1. };

	ODESolver(difue, impl_MP, t0, y0, T, h, out_implMP, stepsave);
	ODESolver(difue, expl_euler, t0, y0, T, h, out_explEV, stepsave);
	ODESolver(difue, gauss2, t0, y0, T, h, out_gauss2, stepsave);

	return 0;
}
