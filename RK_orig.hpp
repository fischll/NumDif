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

  
  virtual bool Step (double t, double h, const ODE_Function & func,
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
    return true;
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

  virtual bool Step(double t, double h, const ODE_Function& func,
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
    int maxcnt = 20;

    while((err > epsilon) && (cnt < maxcnt))
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
    if(cnt == maxcnt)
      return false;
    ynew = yold;
    for (auto i : Range(stages))
      ynew += h * b[i] * yi.Range(i*n,(i+1)*n);
    return true;
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
  virtual int Order() override { return 2; }
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
  virtual int Order() override { return 4; }
};

class Gauss3 : public ImplicitRKMethod
{
public:
  Gauss3() : ImplicitRKMethod(3)
  {
    c = {0.5 - sqrt(15.)/10, 0.5, 0.5 + sqrt(15.)/10};
    b = {5./18, 4./9, 5./18};
    A = {{5./36, 2./9 - sqrt(15.)/15, 5./36 - sqrt(15.)/30 },
         {5./36 + sqrt(15.)/24, 2./9, 5./36 - sqrt(15.)/24 },
         {5./36 + sqrt(15.)/30, 2./9 + sqrt(15.)/15, 5./36}};
  }

  virtual int Order() override { return 6; }
};

class GaussRadau2 : public ImplicitRKMethod
{
public:
  GaussRadau2() : ImplicitRKMethod(2)
  {
    A = {{5./12, -1./12},
         {3./4., 1./4}};
    b = {3./4, 1./4};
    c = {1./3, 1.};
  }
  virtual int Order() override { return 3; }
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
  virtual int Order() override { return 4; }
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
  virtual int Order() override { return 1; }
};
