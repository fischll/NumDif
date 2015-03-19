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
public:
  ExplicitRKMethod (int as) : RungeKuttaMethod (as){ ; }

  
  virtual void Step (double t, double h, const ODE_Function & func,
                     const Vector<> & yold, Vector<> & ynew) const
  {
    int n = yold.Size();

    Vector<> yi(n), ki(n);
    Vector<> all_ki(stages*n);

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
  


class ClassicalRK : public ExplicitRKMethod
{
public:
  ClassicalRK() : ExplicitRKMethod (4)
  {
    Matrix<> A(4,4);
    Vector<> b(4), c(4);

	c = { 0, 0.5, 0.5, 1 };
    
	b = { 1.0 / 6, 2.0 / 6, 2.0 / 6, 1.0 / 6 };

    A = 0.0;
    A(1,0) = 0.5;
    A(2,1) = 0.5;    
    A(3,2) = 1;
    
    SetAbc (A, b, c);
  }
};
