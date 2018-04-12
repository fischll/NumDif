
#include "bla/bla.hpp"
using namespace ngbla;
#include "ode.hpp"
#include "RK_orig.hpp"
#include <math.h>

using namespace std;

class PendulumODEFunction : public ODE_Function
{
  virtual void Eval(double t, const Vector<>& y, Vector<>& f) const override
  {
    f = {y[1], -sin(y[0])};
  }
  virtual void EvalDfDy(double t, const Vector<>& y, Matrix<>&dfdy) const override
  {
    dfdy = 0;
    dfdy(0,1) = 1;
    dfdy(1,0) = -cos(y[0]);
  }
};

int main()
{
  Vector<> phi0 = {M_PI/4, 0};
  PendulumODEFunction f;
  Gauss2 method;
  ofstream out("pendulum.out");
  double h = 1e-1;
  ODESolver(f,method,0,phi0,10000,h,out,1./10/h);
}
