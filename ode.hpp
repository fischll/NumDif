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
  virtual void Step (double t, double h, const ODE_Function & func, 
                     const Vector<> & yold, Vector<> & ynew) const = 0;
};





// the time integration loop
void ODESolver (const ODE_Function & func, const SSM & ssm, 
		double t0, Vector<> & y0, double tend, double h,
		ostream & out, size_t writeout_stepsize=1)
{
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
      t += h; 
	  step++;
    }
}



/* *************** Here are the specific single-step methods *************** */

class ExplicitEuler : public SSM
{
  mutable Vector<> f;
public:
  virtual void Step (double t, double h, const ODE_Function & func,
                     const Vector<> & yold, Vector<> & ynew) const override
  {
    f.SetSize(yold.Size());

    func.Eval (t, yold, f);
    ynew = yold + h * f;
  }
};


class ImprovedEuler : public SSM
{
  mutable Vector<> f;
public:
  virtual void Step (double t, double h, const ODE_Function & func,
                     const Vector<> & yold, Vector<> & ynew) const override
  {
    f.SetSize(yold.Size());

    func.Eval (t, yold, f);
    ynew = yold + h/2.0 * f;

    func.Eval (t+h/2.0, ynew, f);
    ynew = yold + h * f;
  }
};

// von Lorenz eingeblendet
class ImplicitEuler : public SSM
{
public:
  virtual void Step (double t, double h, const ODE_Function & func,
                     const Vector<> & yold, Vector<> & ynew) const override
  {
    Matrix<> DF(yold.Size());
    Identity Id(yold.Size());
    Matrix<> funcdfdy(yold.Size());
    Matrix<> InvDF(yold.Size());

    Vector<> f(yold.Size());
    Vector<> update(yold.Size());

    double err=1;
    double epsilon = 1e-8;

    ynew=yold;

    int cnt=0;

    while ((err > epsilon) && (cnt <20))
      {
 	func.EvalDfDy(t,ynew,funcdfdy);
      
	DF = Id - h * funcdfdy;
	CalcInverse(DF,InvDF);
      
	func.Eval(t+h,ynew,f);

	update = InvDF * (ynew-yold-h*f);
	
	err = L2Norm(update);
	
	ynew -= update;
	cnt++;
      }

  }
};
