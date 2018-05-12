// computes Gaussean integration formula on (0,1) with n points
// in: Numerical algs in C (or, was it the Fortran book ?)
inline void ComputeGaussRule (int n,
			      Vector<double> & xi,
			      Vector<double> & wi)
 {
    //  cout << "compute gauss rule, n = " << n << endl;
    xi.SetSize (n);
    wi.SetSize (n);

    int m = (n+1)/2;
    double p1, p2, p3;
    double pp, z, z1;
    for (int i = 1; i <= m; i++)
      {
	z = cos ( M_PI * (i - 0.25) / (n + 0.5));

	while(1)
	  {
	    p1 = 1;
	    p2 = 0;
	    for (int j = 1; j <= n; j++)
	      {
		p3 = p2;
		p2 = p1;
		p1 = ((2 * j - 1) * z * p2 - (j - 1) * p3) / j;
	      }
	    // p1 is legendre polynomial

	    pp = n * (z*p1-p2) / (z*z - 1);
	    z1 = z;
	    z = z1-p1/pp;

	    if (fabs (z - z1) < 1e-14) break;
	  }

	xi[i-1] = 0.5 * (1 - z);
	xi[n-i] = 0.5 * (1 + z);
	wi[i-1] = wi[n-i] = 1.0 / ( (1  - z * z) * pp * pp);
      }
    //  (*testout) << "Gauss points with n = " << n << ":" << endl;
    //  for (i = 1; i <= n; i++)
    //    (*testout) << xi.Elem(i) << ",  w= " << wi.Elem(i) << endl;
  }





  double  gammln(double xx)
  {
    double x,tmp,ser;
    static double cof[6]={76.18009173,-86.50532033,24.01409822,
			  -1.231739516,0.120858003e-2,-0.536382e-5};

    x=xx-1.0;
    tmp=x+5.5;
    tmp -= (x+0.5)*log(tmp);
    ser=1.0;
    for (int j=0;j<=5;j++) {
      x += 1.0;
      ser += cof[j]/x;
    }
    return -tmp+log(2.50662827465*ser);
  }



  const double  EPS = 3.0e-14;
  const int  MAXIT = 10;

  void ComputeGaussJacobiRule (int n,
			       Vector<double> & x,
			       Vector<double> & w,
			       double alf, double bet)
  {
    x.SetSize (n);
    w.SetSize (n);

    int i,its,j;
    double alfbet,an,bn,r1,r2,r3;
    double a,b,c,p1,p2,p3,pp,temp,z=0,z1;

    for (i=1;i<=n;i++) {
      if (i == 1) {
	an=alf/n;
	bn=bet/n;
	r1=(1.0+alf)*(2.78/(4.0+n*n)+0.768*an/n);
	r2=1.0+1.48*an+0.96*bn+0.452*an*an+0.83*an*bn;
	z=1.0-r1/r2;
      } else if (i == 2) {
	r1=(4.1+alf)/((1.0+alf)*(1.0+0.156*alf));
	r2=1.0+0.06*(n-8.0)*(1.0+0.12*alf)/n;
	r3=1.0+0.012*bet*(1.0+0.25*fabs(alf))/n;
	z -= (1.0-z)*r1*r2*r3;
      } else if (i == 3) {
	r1=(1.67+0.28*alf)/(1.0+0.37*alf);
	r2=1.0+0.22*(n-8.0)/n;
	r3=1.0+8.0*bet/((6.28+bet)*n*n);
	z -= (x[0]-z)*r1*r2*r3;
      } else if (i == n-1) {
	r1=(1.0+0.235*bet)/(0.766+0.119*bet);
	r2=1.0/(1.0+0.639*(n-4.0)/(1.0+0.71*(n-4.0)));
	r3=1.0/(1.0+20.0*alf/((7.5+alf)*n*n));
	z += (z-x[n-4])*r1*r2*r3;
      } else if (i == n) {
	r1=(1.0+0.37*bet)/(1.67+0.28*bet);
	r2=1.0/(1.0+0.22*(n-8.0)/n);
	r3=1.0/(1.0+8.0*alf/((6.28+alf)*n*n));
	z += (z-x[n-3])*r1*r2*r3;
      } else {
	z=3.0*x[i-2]-3.0*x[i-3]+x[i-4];
      }
      alfbet=alf+bet;
      for (its=1;its<=MAXIT;its++) {
	temp=2.0+alfbet;
	p1=(alf-bet+temp*z)/2.0;
	p2=1.0;
	for (j=2;j<=n;j++) {
	  p3=p2;
	  p2=p1;
	  temp=2*j+alfbet;
	  a=2*j*(j+alfbet)*(temp-2.0);
	  b=(temp-1.0)*(alf*alf-bet*bet+temp*(temp-2.0)*z);
	  c=2.0*(j-1+alf)*(j-1+bet)*temp;
	  p1=(b*p2-c*p3)/a;
	}
	pp=(n*(alf-bet-temp*z)*p1+2.0*(n+alf)*(n+bet)*p2)/(temp*(1.0-z*z));
	z1=z;
	z=z1-p1/pp;
	if (fabs(z-z1) <= EPS) break;
      }
      if (its > MAXIT)
	cout << "too many iterations in gaujac";
      x[i-1]=z;

      if (bet == 0.0)
	{
	  w[i-1] = 1.0 / ( (n+alf) * n )
	    *temp*pow(2.0,alfbet)/(pp*p2);
	}
      else
	w[i-1]=
	  exp(  gammln(alf+n) + gammln(bet+n) - gammln(n+1.0) - gammln(n+alfbet+1.0))
	  *temp*pow(2.0,alfbet)/(pp*p2);
    }

    for (int i = 0; i < n; i++)
      {
	w[i] *= 0.5 * pow(1-x[i],-alf) * pow(1+x[i], -bet);
	x[i] = 0.5 * (x[i]+1);
      }
  }







class CollocationMethod : public ImplicitRKMethod
{
private:
  bool radau_method;
public:
  /*
    Generate Gauss or Gauss-Radau Runge-Kutta method
    as .. stage order
    radau .. false -> Gauss,  true -> Radau
  */
  CollocationMethod (int as, bool radau = false)
    : ImplicitRKMethod (as), radau_method(radau)
  {
    Vector<double> ci(as), bi(as);
    Matrix<> aij(as,as);

    if (!radau)
      {
	Vector<> weight(as);
	ComputeGaussRule (as, ci, weight);
      }
    else
      {
	Vector<double> hci(as-1), weight(as-1);
	ComputeGaussJacobiRule (as-1, hci, weight, 1, 0);
	ci.Range(0, as-1) = hci;
	ci(as-1) = 1;
      }

    Matrix<> mat(as,as), inv(as, as);
    Vector<> rhs(as), sol(as);

    for (int j = 0; j < as; j++)
      for (int l = 0; l < as; l++)
	mat(j, l) = pow(ci[l], j);
    CalcInverse (mat, inv);
    // cout << "mat = " << endl << mat << endl;

    for (int i = 0; i < as; i++) // compute row i
      {
	for (int j = 0; j < as; j++)
	  rhs(j) = pow(ci[i], j+1)/(j+1);
	aij.Row(i) = inv * rhs;
      }

    for (int j = 0; j < as; j++)
      rhs(j) = 1.0/(j+1);
    bi = inv * rhs;

    /*
    cout << "ci = " << endl << ci << endl;
    cout << "aij = " << endl << aij << endl;
    cout << "bi = " << endl << bi << endl;
    */
    SetAbc (aij, bi, ci);
  }

  virtual int Order() override
  {
    if (radau_method)
      return stages*2-1;
    else
      return stages*2;
  }

};
