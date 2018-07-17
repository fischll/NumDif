#include "bla/bla.hpp"
using namespace ngbla;
#include "ode.hpp"
#include "RK_orig.hpp"
#include <math.h>


class Diode_ODE_Function : public ODE_Function
{
	double Is; //dioden parameter
	double UT; //dioden parameter
	double R;  //widerstand
	double C;  //kapazität
	double omega; //winkelgeschwindigkeit der Anregungspannung
public:
	Diode_ODE_Function(double Ism, double UTm, double Rm, double Cm, double omegam) { Is = Ism; UT = UTm; R = Rm; C = Cm; omega = omegam; }


	virtual void Eval(double t, const Vector<> & y, Vector<> & f) const
	{
		f(0) = (Is / C)*(exp((sin(omega*t) - y(0)) / UT) - 1) - y(0) / C / R;
	}
};



int main()
{
	ImplicitEuler impl_euler;
	double h = 0.01;

	ofstream out("diode.txt");
	Diode_ODE_Function dio(0.001, 0.2, 1, 1, 1);
	Vector<> y0(1);
	y0(0) = 0; // Anfangsspannung
	ODESolver(dio, impl_euler, 0, y0, 30, h, out, 1); // ODESolver (const ODE_Function & func, const SSM & ssm, double t0, Vector<> & y0, double tend, double h, ostream & out, size_t writeout_stepsize = 1)
	return 0;
}
