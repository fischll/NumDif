// a simple ODE - solver library
// Joachim Schoeberl
// the base class for the right-hand-side f(t,y)

class ODE_Function
{
public:
	// must be overloaded by derived class
	virtual void Eval(double t, const Vector<> & y, Vector<> & f) const = 0;
	virtual void EvalDfDy(double t, const Vector<> & y, Matrix<> & dfdy) const
	{
		// numerical differentiation
		int n = y.Size();
		Vector<> yr(n), yl(n), fr(n), fl(n);
		double eps = 1e-6;
		for (int i = 0; i < n; i++)
		{
			yl = y;  yl(i) -= eps;
			yr = y;  yr(i) += eps;
			Eval(t, yl, fl);
			Eval(t, yr, fr);
			dfdy.Col(i) = 1.0 / (2 * eps) * (fr - fl);
		}
	}
};


// base class for the single-step method
class SSM
{
public:
	// do the step
	virtual bool Step(double t, double h, const ODE_Function & func,
		const Vector<> & yold, Vector<> & ynew) = 0;
	//virtual void StepAdaptive(double t, double hold, double hnew, const ODE_Function & func, const Vector<> & yold, const Vector<> & ynew) = 0;
	virtual int Order() = 0;
};

// the time integration loop
void ODESolver(const ODE_Function & func, SSM & ssm,
	double t0, Vector<> & y0, double tend, double h,
	ostream & out, size_t writeout_stepsize = 1)
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
		ssm.Step(t, h, func, yold, ynew);
		yold = ynew;
		t += h; step++;
	}
}

//time integration loop with adaptive step size
void ODESolverAdaptive(const ODE_Function & func, SSM & base_methode, SSM & estimate_methode, double t0, Vector<> & y0, double tend,
	ostream & out, double epsilon, double hmin = 1e-6, double hmax = 1, double alpha_min = 0.5, double alpha_max = 1.5, double beta = 0.925, size_t writeout_stepsize = 1) 
	/*rechte seite funktion*//*Methode mit niedriger KO*/ /*Methode mit höherer KO*/ /*Startwert Zeit*/ /*Startwert Ort*/ /*Datei zum rausschreiben*/
	/*genauigkeit die man sich wünscht... insgesammt (T-t0)*epsilon*/ /*min Schrittweite*/ /*max Schrittweite*/ /*alpha_min*/ /*alpha_max*/ /*beta*/
{
	int n = y0.Size();
	Vector<> yold(n), ynew(n), ydach(n);
	yold = y0;
	size_t step = 0;
	double sh=0, hold=hmin, hnew=hmin, qh=0, alpha=0, t=t0;
	bool step_ok;

	while (t < tend)
	{
		if (step%writeout_stepsize == 0)
		{
			out << t << " ";
			out << hnew; //Größe vom h
			for (size_t i = 0; i < n; i++)
				out << " " << yold(i);
			out << "\n";
		}

		do{
			hold = hnew;
			step_ok = base_methode.Step(t, hold, func, yold, ynew);
			if (!step_ok) // ! ist die Negation einer boolean Variable
			{
				hnew = hold / 2;
				if (hnew < hmin)
					cout << "Newton convergiert auch mit minimaler Schrittweite nicht." << endl;
				continue;
			}			
			step_ok = estimate_methode.Step(t, hold, func, yold, ydach);
			if (!step_ok) // ! ist die Negation einer boolean Variable
			{
				hnew = hold / 2;
				if (hnew < hmin)
					cout << "Newton convergiert auch mit minimaler Schrittweite nicht." << endl;
				continue;
			}
			sh = sqrt(InnerProduct(ynew - ydach, ynew - ydach)); //Norm
			qh = sh / epsilon / hold;

			if (alpha_min > pow(qh, -1. / base_methode.Order()))
				alpha = alpha_min;
			else
			{
				if (alpha_max < pow(qh, -1. / base_methode.Order()))
					alpha = alpha_max;
				else
					alpha = pow(qh, -1. / base_methode.Order());
			}

			if (hmin > beta*alpha*hold)
				hnew = hmin;
			else
			{
				if (hmax < beta*alpha*hold)
					hnew = hmax;
				else
					hnew = beta * alpha*hold;
			}
		} while (qh > 1 && hnew > hmin); //ein until nachgebaut mit hilfe unseres guten alten freundes DEMORGAN
		t += hnew;
		yold = ynew;
	}
}



/* *************** Here are the specific single-step methods *************** */
class ExplicitEuler : public SSM
{
	Vector<> f;
public:
	virtual bool Step(double t, double h, const ODE_Function & func,
		const Vector<> & yold, Vector<> & ynew) override
	{
		f.SetSize(yold.Size());
		func.Eval(t, yold, f);
		ynew = yold + h * f;
		return true;
	}
	virtual int Order() override { return 1; }
};
class ImprovedEuler : public SSM
{
	Vector<> f;
public:
	virtual bool Step(double t, double h, const ODE_Function & func,
		const Vector<> & yold, Vector<> & ynew) override
	{
		f.SetSize(yold.Size());
		func.Eval(t, yold, f);
	 	ynew = yold + h / 2.0 * f;
		func.Eval(t + h / 2.0, ynew, f);
		ynew = yold + h * f;
		return true;
	}
		virtual int Order() override { return 2; }
};
class ImplicitEuler : public SSM
{
	Matrix<> DF, funcdfdy, InvDF;
	Vector<> f, update;
public:
	virtual bool Step(double t, double h, const ODE_Function & func,
		const Vector<> & yold, Vector<> & ynew) override
	{
		auto n = yold.Size();
		DF.SetSize(n);
		funcdfdy.SetSize(n);
		InvDF.SetSize(n);
		f.SetSize(n);
		update.SetSize(n);
		Identity Id(n);
		double err = 1;
		double epsilon = 1e-8;
		ynew = yold;
		int cnt = 0;
		while ((err > epsilon) && (cnt <20))
		{
			func.EvalDfDy(t + h, ynew, funcdfdy);

			DF = Id - h * funcdfdy;
			CalcInverse(DF, InvDF);

			func.Eval(t + h, ynew, f);
			update = InvDF * (ynew - yold - h * f);

			err = L2Norm(update);

			ynew -= update;
			cnt++;
		}
		return true;
	}
	virtual int Order() override { return 1; }
};
