// a simple ODE - solver library
// Joachim Schoeberl


// the base class for the right-hand-side f(t,y)
class ODE_Function
{
public:
  // must be overloaded by derived class
  virtual void Eval (double t, const Vector<> & y, Vector<> & f) const = 0;

  virtual void EvalDfDy (double t, const Vector<> & y, Matrix<> & dfdy) const
  {
    // numerical differentiation
    int n = y.Size();
    Vector<> yr(n), yl(n), fr(n), fl(n);
    double eps = 1e-6;
    for (int i = 0; i < n; i++)
      {
        yl = y;  yl(i) -= eps;
        yr = y;  yr(i) += eps;
        Eval (t, yl, fl);
        Eval (t, yr, fr);

	dfdy.Col(i) = 1.0/(2*eps) * (fr - fl);
      }
  }
};



// base class for the single-step method
class SSM
{
public:
  // do the step
  virtual bool Step (double t, double h, const ODE_Function & func,
                     const Vector<> & yold, Vector<> & ynew) = 0;
  virtual int Order() = 0;
};





// the time integration loop
void ODESolver (const ODE_Function & func, SSM & ssm,
		double t0, Vector<> & y0, double tend, double h,
		ostream & out, size_t writeout_stepsize=1)
{
  // to be able to write somthing like writeout_stepsize=1./h/10 and still work if h gets big
  if (writeout_stepsize<1) writeout_stepsize=1;
  double t = t0;
  int n = y0.Size();

  Vector<> yold(n), ynew(n);

  yold = y0;
  size_t step = 0;
  while (t < tend)
    {
      if (step%writeout_stepsize == 0)
        {
          out << t;
          for (int i = 0; i < n; i++)
            out << " " << yold(i);
          out << "\n";
        }
      ssm.Step (t, h, func, yold, ynew);
      yold = ynew;
      t += h; step++;
    }
}

void AdaptiveSolver(const ODE_Function& func, SSM& ssm,
                    SSM& ssm_ho, double t0, const Vector<>& y0,
                    double tend, double hstart, ostream& out, double eps)
{
  double alpha_max = 2.;
  double alpha_min = 0.2;
  double beta = 0.95;
  double t = t0;
  auto n = y0.Size();
  Vector<> yold(n), ynew(n), ynew_ho(n);
  yold = y0;
  double h = hstart;
  while (t<tend)
    {
      bool do_step = true;
      while (do_step)
        {
          auto success = ssm.Step(t,h,func,yold,ynew);
          auto success_ho = ssm_ho.Step(t,h,func,yold,ynew_ho);

          if(!success || !success_ho){ h = h/2; continue; }
          // double q = L2Norm(ynew_ho-ynew);
          double q = 0;
          for(auto i : Range(n))
            q += fabs(ynew_ho[i]-ynew[i])/fabs(ynew_ho[i]);
          q /= eps*h;
          if(q <= 1)
            {
              h = beta * min2(alpha_max, pow(q,-1./ssm.Order())) * h;
              do_step = false;
            }
          else
            h = beta * max2(alpha_min, pow(q,-1./ssm.Order())) * h;
        }
      yold = ynew_ho;
      t += h;
      out << t;
      for(auto i : Range(ynew_ho.Size()))
        out << " " << ynew_ho[i];
      out << " " << h << "\n";
    }
}








/* *************** Here are the specific single-step methods *************** */



class ExplicitEuler : public SSM
{
  Vector<> f;
public:
  virtual bool Step (double t, double h, const ODE_Function & func,
                     const Vector<> & yold, Vector<> & ynew) override
  {
    f.SetSize(yold.Size());
    func.Eval (t, yold, f);
    ynew = yold + h * f;
    return true;
  }
  virtual int Order() override { return 1; }
};


class ImprovedEuler : public SSM
{
  Vector<> f;
public:
  virtual bool Step (double t, double h, const ODE_Function & func,
                     const Vector<> & yold, Vector<> & ynew) override
  {
    f.SetSize(yold.Size());

    func.Eval (t, yold, f);
    ynew = yold + h/2.0 * f;

    func.Eval (t+h/2.0, ynew, f);
    ynew = yold + h * f;
    return true;
  }

  virtual int Order() override { return 1; }
};


class ImplicitEuler : public SSM
{
  Matrix<> DF, funcdfdy, InvDF;
  Vector<> f, update;

public:
  virtual bool Step (double t, double h, const ODE_Function & func,
                     const Vector<> & yold, Vector<> & ynew) override
  {
    auto n = yold.Size();
    DF.SetSize(n);
    funcdfdy.SetSize(n);
    InvDF.SetSize(n);
    f.SetSize(n);
    update.SetSize(n);
    Identity Id(n);

    double err=1;
    double epsilon = 1e-8;

    ynew=yold;

    int cnt=0;

    while ((err > epsilon) && (cnt <20))
      {
 	func.EvalDfDy(t+h,ynew,funcdfdy);
      
	DF = Id - h * funcdfdy;
	CalcInverse(DF,InvDF);
      
	func.Eval(t+h,ynew,f);

	update = InvDF * (ynew-yold-h*f);
	
	err = L2Norm(update);
	
	ynew -= update;
	cnt++;
      }
    if(cnt == 20)
      return false;
    return true;
  }
  virtual int Order() override { return 1; }
};
