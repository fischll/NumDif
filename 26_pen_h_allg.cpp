
#include "bla/bla.hpp"
using namespace ngbla;
#include "hamilton.hpp"
#include <math.h>
using namespace std;

class StringPendulum : public Hamiltonian
{
public:
  virtual double Eval(const Vector<>&p , const Vector<>&q) const override
  {
    return 1./2 * p[0] * p[0] - cos(q[0]);
  }
  virtual double EvalDp(const Vector<>& p, const Vector<>& q, Vector<>& dHdp) const override
  {
    dHdp[0] = p[0];
  }
  virtual double EvalDq (const Vector<>&p, const Vector<>& q, Vector<>& dHdq) const override
  {
    dHdq[0] = sin(q[0]);
  }
  virtual bool IsSeperable() const override { return true; }
};


int main()
{
  Vector<> p = { 1. };
  Vector<> q = { 0. };
  StringPendulum H;
  //SymplecticEuler method;
  StoermerVerlet method;
  ofstream out("bsp26.out");
  HamiltonianSolve(H, method, p, q, 100., 0.1, out);
}
