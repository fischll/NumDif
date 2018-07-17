#include "bla/bla.hpp"
using namespace ngbla;
#include "ode.hpp"
#include "RK_orig.hpp"
#include <math.h>


class ChemicalReactions_ODE_Function : public ODE_Function
{
protected:
	Vector<> k;
public:
	ChemicalReactions_ODE_Function(Vector<> & mk) {
		k.SetSize(mk.Size());
		k = mk; 
	}

	virtual void Eval(double t, const Vector<> & y, Vector<> & f) const
	{
		f(0) = -k(0)*y(0)*y(1) - k(2)*y(0)*y(2) + k(3)*y(2)*y(2);
		f(1) = -k(0)*y(0)*y(1) - k(1)*y(1)*y(2) + k(4)*y(4);
		f(2) = k(0)*y(0)*y(1) - k(1)*y(1)*y(2) + k(2)*y(0)*y(2) - 2 * k(3)*pow(y(2), 2);
		f(3) = k(0)*y(0)*y(1) + k(1)*y(1)*y(2) + k(3)*pow(y(2), 2);
		f(4) = k(2)*y(0)*y(2) - k(4)*y(4);
	}
};



int main()
{
	Gauss2 gauss2;
	ImplMP implMP;

	double hmin = 1e-10;
	double hmax = 1e-2;
	double alpha_min = 0.35;
	double alpha_max = 1.75;
	double beta = 0.925;
	double t0 = 0;
	double tend =  200;
	double epsilon = 1e-7;
	int writeout_stepsize = 1;


	ofstream out("ChemicalReaction.txt");
	Vector<> k = { 1.34, 1.6e9, 8e3, 4e7, 1e0 };
	Vector<> y0 = { 0.05, 1e-4, 1e-10, 1e-1, 1e-4 };
	ChemicalReactions_ODE_Function oregano(k);

	ODESolverAdaptive(oregano, implMP, gauss2, t0, y0, tend, out, epsilon, hmin, hmax, alpha_min, alpha_max, beta, writeout_stepsize);
	return 0;
}
