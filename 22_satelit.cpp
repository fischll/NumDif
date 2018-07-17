#include "bla/bla.hpp"
using namespace ngbla;
#include "ode.hpp"
#include "RK_orig.hpp"
#include <math.h>


class Satelit_Motion : public ODE_Function
{
protected:
	double mu;
public:
  Satelit_Motion(double mmu) {mu= mmu;}

	virtual void Eval(double t, const Vector<> & y, Vector<> & f) const
	{
        f(0)=y(1);
	f(1)=y(0) + 2*y(3) - (1-mu)*(y(0)+mu)/pow(pow(y(0)+mu,2)+pow(y(2),2),1.5) - mu*(y(0)-(1-mu))/pow( pow(y(0)-(1-mu),2) + pow(y(2),2), 1.5);
	f(2)=y(3);
	f(3)=y(2)-2*y(1)-(1-mu)*y(2)/pow(pow(y(0)+mu,2)+pow(y(2),2) , 1.5) - mu*y(2)/pow( pow(y(0)-(1-mu),2)+pow(y(2),2) ,1.5);
	}
};



int main()
{
  Heun_RK RK3;
  Classical_expl_RK RK4;
  double hmin = 1e-6;
  double hmax = 1e-1;
  double alpha_min = 0.35;
  double alpha_max = 1.75;
  double beta = 0.925;
  double t0 = 0;
  double tend = 17.0652166;
  double epsilon = 1.3e-6;//1e-8;
  int writeout_stepsize = 1;
  double mu = 0.012277471;

  Satelit_Motion satelit(mu);
  
  ofstream out("satelit.txt");
  Vector<> y0 = { 0.994, 0, 0, -2.0015851063790825};
  
  ODESolverAdaptive(satelit, RK3, RK4, t0, y0, tend, out, epsilon, hmin, hmax, alpha_min, alpha_max, beta, writeout_stepsize);
  return 0;
}
