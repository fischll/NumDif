// Runge Kutta methods 
// Joachim Schoeberl


class MyFunction {
public:
	virtual void Eval(Vector<> & x, Vector<> & f) const = 0;

	virtual void Evaldfdx(Vector<> & x, Matrix<> & dfdx, double eps = 1e-6) const {
		// numerical differentiation
		int n = x.Size();
		Vector<> xr(n), xl(n), fr(n), fl(n);
		for (int i = 0; i < n; i++)
		{
			xl = x;
			xl(i) -= eps;
			xr = x;
			xr(i) += eps;
			Eval(xl, fl);
			Eval(xr, fr);

			dfdx.Col(i) = 1.0 / (2 * eps) * (fr - fl);
		}
	}
};
class Newton
{
public:
	void newton(Vector<> & zold, Vector<> & znew, const MyFunction & func, double eps = 10e-8, int maxcnt = 20)
	{
		znew = zold;
		Matrix<> Df(zold.Size());
		Matrix<> InvDf(zold.Size());

		Vector<> f(zold.Size());
		Vector<> update(zold.Size());
		int cnt = 0;
		double err = eps + 1;

		while ((err > eps) && (cnt < maxcnt))
		{
			func.Evaldfdx(znew, Df);
			CalcInverse(Df, InvDf);
			func.Eval(znew, f);

			update = InvDf * (-f);

			err = L2Norm(update);
			znew += update;
			cnt++;
		}
	}
};

class RungeKuttaMethod : public SSM
{
protected:
	int stages;
	Matrix<> A;
	Vector<> b, c;
public:
	RungeKuttaMethod(int s)
		: stages(s), A(s, s), b(s), c(s)
	{
		;
	}

	void SetAbc(const Matrix<> & aa,
		const Vector<> & ab,
		const Vector<> & ac)
	{
		A = aa;
		b = ab;
		c = ac;
	}
};


//============================implicitRKMethod===========================
class ImplicitRKMethod : public RungeKuttaMethod
{
public:
	ImplicitRKMethod(int as) : RungeKuttaMethod(as) { ; }

	virtual bool Step(double t, double h, const ODE_Function & func, const Vector<> & yold, Vector<> & ynew) override
	{
		int n = yold.Size(); //f: R^n -> R^n
		double eps = 1e-8;
		int maxcnt = 10;
		int cnt = 0;
		double err = eps + 1;

		Vector<> y(stages*n);
		Vector<> k(stages*n);
		Vector<> f(stages*n);
		Vector<> fi(n);
		Vector<> yi(n);
		Vector<> F(stages*n); //Psi
		Vector<> time(stages);
		Matrix<> dfdy(n);
		Matrix<> DF(stages*n);
		Matrix<> InvDF(stages*n);
		Identity Id(stages*n);
		Vector<> update(stages*n);
		fi = 317;
		for (int i = 0; i < stages; i++) // Quadraturknoten, Startwerte
		{
			time(i) = t + c(i)*h;
			k.Range(i*n, (i + 1)*n) = yold;
		}
		//Newton
		//Newton verfahren wind auf die funktion F(k) := k - f(t + c(i)*h, yold + h* sum(A(i,l)*k(l)))
		while ((err > eps) && (cnt < maxcnt))
		{
			for (int i = 0; i < stages; i++) // Auswertungsstellen y
			{
				y.Range(i*n, (i + 1)*n) = yold;
				for (int l = 0; l < stages; l++)
					y.Range(i*n, (i + 1)*n) += h * A(i, l) * k.Range(l*n, (l + 1)*n);
			}

			for (int i = 0; i < stages; i++) // f(time(i),y(i)) auswerten
			{
				yi = y.Range(i*n, (i + 1)*n);
				func.Eval(time(i), yi, fi);
				f.Range(i*n, (i + 1)*n) = fi;
			}

			for (int i = 0; i<stages; i++) // F erstellen
				F.Range(i*n, (i + 1)*n) = k.Range(i*n, (i + 1)*n) - f.Range(i*n, (i + 1)*n);

			DF = Id;
			for (int i = 0; i < stages; i++)
			{
				yi = y.Range(i*n, (i + 1)*n);
				func.EvalDfDy(time(i), yi, dfdy);
				for (int m = 0; m < stages; m++)
					for (int e1 = 0; e1 < n; e1++) //navigieren in der kleinen Blockmatrix (e1,e2)
						for (int e2 = 0; e2 < n; e2++)
							DF(i*n + e1, m*n + e2) -= A(i, m) * h * dfdy(e1, e2);
			}

			CalcInverse(DF, InvDF);

			update = InvDF * (-F);
			err = L2Norm(update);
			k += update;
			cnt++;
		}

		ynew = yold;
		for (int i = 0; i < stages; i++)
			ynew += h * b(i) * k.Range(i*n, (i + 1)*n);
		if (cnt == maxcnt)
			return false;
		else
			return true;
	}
};
class ImplMP : public ImplicitRKMethod
{
public:
	ImplMP() : ImplicitRKMethod(1)
	{
		Matrix<> A(1, 1);
		Vector<> b(1), c(1);

		c = { 0.5 };

		b = { 1. };

		A = 0.5;

		SetAbc(A, b, c);
	}
	virtual int Order() override { return 1; }
};
class Gauss2 : public ImplicitRKMethod
{
public:
	Gauss2() : ImplicitRKMethod(2)
	{
		Matrix<> A(2, 2);
		Vector<> b(2), c(2);

		c = { (1. / 2) - sqrt(3) / 6, (1. / 2) + sqrt(3) / 6 };

		b = { 1. / 2, 1. / 2 };

		A = 1. / 4;
		A(0, 1) -= sqrt(3) / 6;
		A(1, 0) += sqrt(3) / 6;

		SetAbc(A, b, c);
	}

	virtual int Order() override { return 3; }
};
class ImplEV_RK : public ImplicitRKMethod
{
public:
	ImplEV_RK() : ImplicitRKMethod(1)
	{
		Matrix<> A(1, 1);
		Vector<> b(1), c(1);

		c = { 1. };

		b = { 1. };

		A = 1.;

		SetAbc(A, b, c);
	}
	virtual int Order() override{ return 1; }
};



//============================explicitRKMethod===========================
class ExplicitRKMethod : public RungeKuttaMethod
{
	Vector<> yi, ki, all_ki;
public:
	ExplicitRKMethod(int as) : RungeKuttaMethod(as) { ; }


	virtual bool Step(double t, double h, const ODE_Function & func,
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
				yi += h * A(i, j) * all_ki.Range(j*n, (j + 1)*n);

			func.Eval(ti, yi, ki);
			all_ki.Range(i*n, (i + 1)*n) = ki;
		}


		ynew = yold;
		for (int i = 0; i < stages; i++)
			ynew += h * b(i) * all_ki.Range(i*n, (i + 1)*n);

		return true;
	}
};


class Classical_expl_RK : public ExplicitRKMethod
{
public:
	Classical_expl_RK() : ExplicitRKMethod(4)
	{
		c = { 0, 0.5, 0.5, 1 };
		b = { 1.0 / 6, 2.0 / 6, 2.0 / 6, 1.0 / 6 };

		A = 0.0;
		A(1, 0) = 0.5;
		A(2, 1) = 0.5;
		A(3, 2) = 1;
		SetAbc(A, b, c);
	}
	virtual int Order() override { return 4; }//bin mir nicht sicher
};


class ImprovedEulerRK : public ExplicitRKMethod
{
public:
	ImprovedEulerRK() : ExplicitRKMethod(2)
	{
		c = { 0, 0.5 };
		b = { 0.0, 1.0 };

		A = 0.0;
		A(1, 0) = 0.5;
		SetAbc(A, b, c);
	}
	virtual int Order() override { return 2; }
};


class Heun_RK : public ExplicitRKMethod
{
public:
	Heun_RK() : ExplicitRKMethod(3)
	{
		c = {0., 1. / 3, 2. / 3 };
		b = { 1. / 4, 0., 3. / 4 };

		A = 0.0;
		A(1,0) = 1. / 3;
		A(2,1) = 2. / 3;
		SetAbc(A, b, c);
	}
	virtual int Order() override { return 3; }
};

class Bsp16 : public ImplicitRKMethod
{
public:
	Bsp16() : ImplicitRKMethod(2)
	{
		c = { 1. / 3, 1.};
		b = { 3./4, 1. / 4 };

		A(0,0) = 5. / 12;
		A(0,1) = -1. / 12;
		A(1,0) = 3. / 4;
		A(1,1) = 1. / 4;
		SetAbc(A, b, c);
	}
	virtual int Order() override { return 3; }
};