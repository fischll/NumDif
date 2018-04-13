#include "bla/bla.hpp"
using namespace ngbla;
#include "ode.hpp"
#include "RK_orig.hpp"
#include <math.h>


class fktasdf : public MyFunction
{
public:	
	fktasdf() {  }

	virtual void Eval(Vector<> & x, Vector<> & f) const
	{
		//f(0)=x(0);
		//f(1)=x(1);
		f(0) = pow(x(0),2)+x(1)*x(1)-1;
		f(1) = x(0)+x(1)+1;
	}
};


int main()
{
	Vector<> start = { 1.1, 0.9 };
	Vector<> out(2);

	fktasdf id;
	Newton myNewton;
	myNewton.newton(start, out, id);
		
	
	cout << "out = " << out << endl;
	return 0;
}