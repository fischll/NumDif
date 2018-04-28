#include "bla/bla.hpp"
using namespace ngbla;
#include "ode.hpp"
#include "RK_orig.hpp"
#include "hamilton_orig.hpp"
#include <math.h>


class Pendulum_Hamilton : public Hamilton_Function
{
public:
  Pendulum_Hamilton() { }

  virtual double EvalV(const Vector<> & q) const
  {
    return -cos(q(1));
  }
  virtual double EvalT(const Vector<> & p) const
  {
    return 1./2*pow(p(1),2);
  }
};



int main()
{
  SymplecticEV symplEV;
  double h = 0.01;
  double t0=0;
  double tend = 10;

  ofstream out("PendulumH.txt");
  Pendulum_Hamilton pen();
  Vector<> p0(1);
  Vector<> q0(1);
  p0=1.;
  q0=0;
  ODESolver_Hamilton(pen, symplEV, t0, p0, q0, tend, h, out, 1);
  return 0;
}
