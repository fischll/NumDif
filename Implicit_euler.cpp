// compile with
// g++ ode_demo.cpp bla/calcinverse.cpp bla/exception.cpp bla/localheap.cpp -std=c++11 -o ode_demo -fmax-errors=2 -fdiagnostics-color=auto
//


// a simple linear algebra library
#include "bla/bla.hpp"
#include "ode.hpp"
#include "RK_orig.hpp"

using namespace ngbla;


/* ******************* The ODEs I want to solve  ******************** */

/*
//  f(t,y) = a y 
class My_First_ODE_Function : public ODE_Function
{
	double a;

public:
	My_First_ODE_Function(double aa) { a = aa; }

	virtual void Eval(double t, const Vector<> & y, Vector<> & f) const
	{
		f = a * y;
	}
};

*/




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
	/*
	ExplicitEuler expl_euler;
	ImprovedEuler impr_euler;
	ImprovedEulerRK RK_impr_euler;
	*/

	//ofstream out("data.out");
	//My_First_ODE_Function func(1);
	//Vector<> y0(1);  // initial conditions
	//y0(0) = 1.0;
	//ODESolver(func, expl_euler, 0, y0, 10, 0.1, out);


	ofstream out("Pendulum.out");
	Pendulum_ODE_Function pen(1, 1);
	Vector<> y0(2);
	y0ms(0) = Pi/2;
	y0ms(1) = 0;
	ODESolver(pen, impl_euler, 0, y0, 1000, 0.1, out);

	//ofstream out3("mass_spring_RK.out");
	//ODESolver(ms, RK_impr_euler, 0, y0ms, 1000, 0.1, out3);

	return 0;
}
