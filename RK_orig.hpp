// Runge Kutta methods 
// Joachim Schoeberl


class RungeKuttaMethod : public SSM
{
protected:
  int stages;
  Matrix<> A;
  Vector<> b,c;
public:
  RungeKuttaMethod (int s)
    : stages(s), A(s,s), b(s), c(s) 
  { ; }
 
  void SetAbc (const Matrix<> & aa,
	       const Vector<> & ab,
	       const Vector<> & ac)
  {
    A = aa;
    b = ab;
    c = ac;
  }
};



class ExplicitRKMethod : public RungeKuttaMethod
{
  Vector<> yi, ki, all_ki;
public:
  ExplicitRKMethod (int as) : RungeKuttaMethod (as){ ; }

  
  virtual void Step (double t, double h, const ODE_Function & func,
                     const Vector<> & yold, Vector<> & ynew) override
  {
    int n = yold.Size();
    yi.SetSize(n);
    ki.SetSize(n);
    all_ki.SetSize(stages*n);

    for (int i = 0; i < stages; i++)
      {
	double ti = t + h * c(i);
	yi = yold;
	for (int j = 0; j < i; j++)
	  yi += h * A(i,j) * all_ki.Range (j*n, (j+1)*n);
	func.Eval (ti, yi, ki);
	all_ki.Range(i*n, (i+1)*n) = ki;
      }


    ynew = yold;
    for (int i = 0; i < stages; i++)
      ynew += h * b(i) * all_ki.Range (i*n, (i+1)*n);
  }
};

class ImplicitRKMethod : public RungeKuttaMethod
{
private:
  Vector<> yi, farg, update, F, yi_old, fi;
  Matrix<> dF, tmpmat, InvDF;
  double epsilon = 1e-8;
public:
  ImplicitRKMethod (size_t as) : RungeKuttaMethod(as) { ; }

  virtual void Step(double t, double h, const ODE_Function& func,
                    const Vector<>& yold, Vector<>& ynew) override
  {
    size_t n = yold.Size();
    yi.SetSize(n*stages);
    farg.SetSize(n);
    update.SetSize(n*stages);
    F.SetSize(n * stages);
    fi.SetSize(n);
    dF.SetSize(n*stages);
    tmpmat.SetSize(n);
    InvDF.SetSize(n*stages);

    for (auto i : Range(stages))
      {
        yi.Range(i*n,(i+1)*n) = yold;
      }
    double err = 1.;
    int cnt = 0;

    while((err > epsilon) && (cnt < 20))
      {
        F = yi;
        dF = Identity(n*stages);
        for (auto i : Range(stages))
          {
            // F
            farg = yold;
            for (auto j : Range(stages))
              farg += h * A(i,j) * yi.Range(j*n,(j+1)*n);
            func.Eval(t + c(i)*h,farg,fi);
            F.Range(i*n,(i+1)*n) -= fi;
            // DF
            func.EvalDfDy(t+c(i)*h, farg, tmpmat);
            for (auto j : Range(stages))
              dF.Rows(i*n,(i+1)*n).Cols(j*n,(j+1)*n) -= h * A(i,j) * tmpmat;
          }
        CalcInverse(dF,InvDF);
        update = InvDF * F;
        err = L2Norm(update);
        cnt++;
        yi -= update;
      }
    if(cnt == 20)
      throw Exception("Newton didn't converge!");
    ynew = yold;
    for (auto i : Range(stages))
      ynew += h * b[i] * yi.Range(i*n,(i+1)*n);
  }
};

class ImplicitMP : public ImplicitRKMethod
{
public:
  ImplicitMP() : ImplicitRKMethod(1)
  {
    c = {0.5};
    b = {1.};
    A(0,0) = 0.5;
  }
};

class Gauss2 : public ImplicitRKMethod
{
public:
  Gauss2() : ImplicitRKMethod(2)
  {
    c = { 0.5 - sqrt(3.)/6., 0.5 + sqrt(3.)/6.};
    b = {0.5, 0.5};
    A = {{1./4, 1./4-sqrt(3.)/6},{1./4 + sqrt(3.)/6, 1./4}};
  }
};


class ClassicalRK : public ExplicitRKMethod
{
public:
  ClassicalRK() : ExplicitRKMethod (4)
  {
    c = { 0, 0.5, 0.5, 1 };
    b = { 1.0 / 6, 2.0 / 6, 2.0 / 6, 1.0 / 6 };

    A = 0.0;
    A(1,0) = 0.5;
    A(2,1) = 0.5;    
    A(3,2) = 1;
  }
};


class ImprovedEulerRK : public ExplicitRKMethod
{
public:
  ImprovedEulerRK() : ExplicitRKMethod (2)
  {
    c = { 0, 0.5 };
    b = { 0.0, 1.0 };

    A = 0.0;
    A(1,0) = 0.5;
    
  }
};
