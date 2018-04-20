// compile with
// g++ ode_demo.cpp bla/calcinverse.cpp bla/exception.cpp bla/localheap.cpp -std=c++11 -o ode_demo -fmax-errors=2 -fdiagnostics-color=auto
//


// a simple linear algebra library
#include "bla/bla.hpp"
#include "ode.hpp"
#include "RK_orig.hpp"

using namespace ngbla;


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

	ofstream out("Pendulum.txt");
	Pendulum_ODE_Function pen(1, 1);
	Vector<> y0(2);
	y0ms(0) = Pi/2;
	y0ms(1) = 0;
	ODESolver(pen, impl_euler, 0, y0, 1000, 0.1, out);
	return 0;
}
