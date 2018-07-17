
class Hamiltonian
{
public:
  virtual double Eval(const Vector<>&p , const Vector<>&q) const = 0;
  virtual double EvalDp(const Vector<>& p, const Vector<>& q, Vector<>& dHdp) const = 0;
  virtual double EvalDq (const Vector<>&p, const Vector<>& q, Vector<>& dHdq) const = 0;
  virtual bool IsSeperable() const { return false; }
};

class HamiltonianSSM
{
public:
  virtual void Step(double t, double h, const Hamiltonian& H, Vector<>& p, Vector<>& q) = 0;
};

class SymplecticEuler : public HamiltonianSSM
{
private:
  // we assume that p and q have same size
  Vector<> dH;
public:
  virtual void Step(double t, double h, const Hamiltonian& H, Vector<>& p, Vector<>& q) override
  {
    dH.SetSize(p.Size());
    if (H.IsSeperable())
      {
        H.EvalDq(p, q,dH);
        p -= h * dH;
        H.EvalDp(p, q, dH);
        q += h * dH;
      }
    else
      throw "Not seperable not implemented!";
  }
};

class StoermerVerlet : public HamiltonianSSM
{
private:
  Vector<> dH;
public:
  virtual void Step(double t, double h, const Hamiltonian& H, Vector<>& p, Vector<>& q) override
  {
    dH.SetSize(p.Size());
    if(H.IsSeperable())
      {
        H.EvalDq(p,q,dH);
        p -= h/2 * dH;
        H.EvalDp(p, q, dH);
        q += h * dH;
        H.EvalDq(p, q, dH);
        p += - h/2 * dH;
      }
    else
      throw "Not seperable not implemented!";
  }
};

void HamiltonianSolve(const Hamiltonian& H, HamiltonianSSM& ssm, Vector<>& p,
                      Vector<>& q, double tend, double h, ostream& out)
{
  double t = 0;
  while(t < tend)
    {
      out << t;
      for (auto i : Range(p.Size()))
          out << " " << p(i);
      for (auto i : Range(q.Size()))
        out << " " << q(i);
      out << " " << H.Eval(p,q);
      out << "\n";
      ssm.Step(t,h,H,p,q);
      t += h;
    }
}
