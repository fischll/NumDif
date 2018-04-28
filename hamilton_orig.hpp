//ogleidet von ode.hpp

class Hamilton_Function
{
public:
  virtual double EvalV(const Vector<> & q)const;
  virtual double EvalT(const Vector<> & p)const ;
  virtual double Eval(const Vector<> & p, const Vector<> & q) const
  {
    return EvalV(q) + EvalT(p);
  }
  virtual void EvalDV(const Vector<> & q, Vector<> & DV) const{
    // numerical differentiation
    int n = q.Size();
    Vector<> qr(n), ql(n);
    double Vr(n), Vl(n);
    double eps = 1e-6;
    for (int i = 0; i < n; i++)
      {
	ql = q;  ql(i) -= eps;
	qr = q;  qr(i) += eps;
	Vl = EvalV(ql);
	Vr = EvalV(qr);
	DV(i) = 1.0 / (2 * eps) * (Vr - Vl);
      }
  }
  virtual void EvalDT(const Vector<> & p, Vector<> & DT) const{
    // numerical differentiation
    int n = p.Size();
    Vector<> pr(n), pl(n);
    double Tr(n), Tl(n);
    double eps = 1e-6;
    for (int i = 0; i < n; i++)
      {
	pl = p;  pl(i) -= eps;
	pr = p;  pr(i) += eps;
	Tl = EvalT(pl);
	Tr = EvalT(pr);
	DT(i) = 1.0 / (2 * eps) * (Tr - Tl);
      }
  }
  /*virtual void EvaldHdp(const Vector<> & p, const Vector<> & q, Vector<> & dHdp)	{
  // numerical differentiation
  int n = q.Size();
  Vector<> pr(n), pl(n);
  double Hr(n), Hl(n);
  double eps = 1e-6;
  for (int i = 0; i < n; i++)
  {
  pl = p;  pl(i) -= eps;
  pr = p;  pr(i) += eps;
  Hl = Eval(pl, q);
  Hr = Eval(pr, q);
  dHdp(i) = 1.0 / (2 * eps) * (Hr - Hl);
  }
  }
  virtual void EvaldHdq(const Vector<> & p, const Vector<> & q, Vector<> & dHdq)	{
  // numerical differentiation
  int n = p.Size();
  Vector<> qr(n), ql(n);
  double Hr(n), Hl(n);
  double eps = 1e-6;
  for (int i = 0; i < n; i++)
  {
  ql = q;  ql(i) -= eps;
  qr = q;  qr(i) += eps;
  Hl = Eval(p, ql);
  Hr = Eval(p, qr);
  dHdq(i) = 1.0 / (2 * eps) * (Hr - Hl);
  }
  }*/
};



class SSM_Hamilton
{
public:
  // do the step
  virtual bool Step(double h, const Hamilton_Function & func,
		    const Vector<> & pold, const Vector<> & qold, Vector<> & pnew, Vector<> & qnew) = 0;
  //virtual void StepAdaptive(double t, double hold, double hnew, const ODE_Function & func, const Vector<> & yold, const Vector<> & ynew) = 0;
  virtual int Order() = 0;
};

// the time integration loop
void ODESolver_Hamilton(const Hamilton_Function & func, SSM_Hamilton & ssm,
			double t0, Vector<> & p0, Vector<> & q0, double tend, double h,
			ostream & out, size_t writeout_stepsize = 1)
{
  double t = t0;
  int n = p0.Size();
  Vector<> pold(n), pnew(n), qold(n), qnew(n);
  pold=p0;
  qold=q0;
  size_t step = 0;
  while (t < tend)
    {
      if (step%writeout_stepsize == 0)
	{
	  out << t;
	  for (int i = 0; i < n; i++)
	    out << " " << pold(i) << " " << qold(i);
	  out << "\n";
	}
      ssm.Step(h, func, pold, qold, pnew, qnew);
      pold=pnew;
      qold=qnew;
      t += h; step++;
    }
}


class SymplecticEV : public SSM_Hamilton
{
  Vector<> DV, DT;
public:
  virtual bool Step( double h, const Hamilton_Function & func,
		     const Vector<> & pold, const Vector<> & qold, Vector<> & pnew, Vector<> & qnew) override
  {
    DV.SetSize(pold.Size());
    DT.SetSize(qold.Size());
    
    func.EvalDV(qold,DV);
    pnew = pold - h*DV;
    func.EvalDT(pnew,DT);
    qnew = pold + h*DT;
    return true;
  }
  virtual int Order() override {return 1;}
};
