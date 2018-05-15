// compile with
// g++ rattle.cpp pendulum_DAE.cpp ../bla/calcinverse.cpp ../bla/exception.cpp ../bla/localheap.cpp -std=c++11 -o test -lglut -lGLU -lGL
//

#include "../bla/bla.hpp"
using namespace ngbla;

#ifndef _WIN32
	#include <unistd.h>
#endif
#include "rattle.hpp"

#include <glut.h>



/* ******************* The ODEs I want to solve  ******************** */

class Pendulum : public ConstrainedHamiltonian
{
  double m1;
  double m2;
  double g;
  double l1;
  double l2;
public:
  Pendulum () { m1 = 5; m2 = 1; g = 1; l1=1; l2=1; }

  virtual int Dim () const { return 4; }
  virtual int DimConstraints () const { return 2; }


  virtual double Eval (double t, const Vector<> & q, const Vector<> & p) const 
  {
    return (p(0) * p(0) + p(1) * p(1))/m1/2 + q(1)*m1*g + (p(2) * p(2) + p(3) * p(3))/m2/2 + q(3)*m2*g  + 1;//der einser ist Anfangsenergie
  }
  virtual void EvalDq (double t, const Vector<> & q, const Vector<> & p, Vector<> & Dq) const
  {
    Dq(0) = 0.;
    Dq(1) = m1*g;
    Dq(2) = 0.;
    Dq(3) = m2*g;
  }
  virtual void EvalDp (double t, const Vector<> & q, const Vector<> & p, Vector<> & Dp) const 
  {
    Dp(0) = p(0)/m1;
    Dp(1) = p(1)/m1;
    Dp(2) = p(2)/m2;
    Dp(3) = p(3)/m2;
  }
  virtual void EvalDpDp (double t, const Vector<> & q, const Vector<> & p, Matrix<> & DpDp) const 
  {
    DpDp=0.;
    DpDp(0,0) = 1./m1;
    DpDp(1,1) = 1./m1;
    DpDp(2,2) = 1./m2;
    DpDp(3,3) = 1./m2;
  }

  virtual void Constraint (double t, const Vector<> & q, const Vector<> & g) const 
  {
    g(0) = q(0) * q(0) + q(1) * q(1) - l1*l1;
    g(1) = (q(2)-q(0))*(q(2)-q(0)) + (q(3)-q(1))*(q(3)-q(1)) - l2*l2; 
  }
  virtual void ConstraintDq (double t, const Vector<> & q, Matrix<> & Dq) const
  {
    Dq(0,0) = 2 * q(0);
    Dq(0,1) = 2 * q(1);
    Dq(0,2) = 0 ;
    Dq(0,3) = 0 ;
    Dq(1,0) = -2*(q(2)-q(0));
    Dq(1,1) = -2*(q(3)-q(1));
    Dq(1,2) = 2* (q(2)-q(0));
    Dq(1,3) = 2* (q(3)-q(1));
  }


  //=========== GRAFIK ==========
  virtual void Redraw (const Vector<> & q) const
  {   
    glClear(GL_COLOR_BUFFER_BIT);		/* clear the display */

    double x1 = q(0);
    double y1 = q(1);
    double x2 = q(2);
    double y2 = q(3);

    DrawBar (0, 0, x1, y1);
    DrawBar (x1,y1,x2,y2);
    DrawMass (x1, y1, 0.1);
    DrawMass (x2, y2, 0.1);
  }

  void DrawBar (double ax, double ay, double bx, double by) const
  {
    glColor3f(1.0, 0, 0);	
    glLineWidth(3);

    glBegin(GL_LINES);	
    glVertex2d(ax, ay);	
    glVertex2d(bx, by);
    glEnd();
  }

  void DrawMass (double cx, double cy, double r) const
  {
    glColor3f(0.0, 1.0, 0.0);	
    glBegin(GL_POLYGON);
    for (int j = 0; j < 20; j++)
      {
        glVertex2d (cx+r*sin(2*M_PI*j/10), 
                    cy+r*cos(2*M_PI*j/10));
      }
    glEnd();
  }
};











ODESolver * psolver;


void displayCB(void)		/* function called whenever redisplay needed */
{
  psolver -> Redraw();
  glutSwapBuffers();
}

bool working = 0;


void keyCB(unsigned char key, int x, int y)	/* called on key press */
{
  if( key == 'q' ) exit(0);
  if( key == 's' ) 
    {
      psolver -> Step();
      displayCB();
    }
      
  if( key == 'b' ) working = 1;
  if( key == 'e' ) working = 0;
}

void idlefunction ()         /* function called when nothing else to do */
{
  if (working)
    {
		for (int i = 0; i < 10; i++)
		psolver -> Step();
#ifndef _WIN32
		usleep(2000);
#endif
      glutPostRedisplay();
      // displayCB();
    }
}





int main (int argc, char ** argv)
{
  Pendulum pendulum;
  Rattle ssm;

  Vector<> q0(4), p0(4);
  p0 = 0.;
  q0 = 0.;
  q0(0) = 1.;
  q0(1) = 0.;
  q0(2) = 1.;
  q0(3) = -1;

  ODESolver solver(pendulum, ssm, 0, q0, p0, 100000, 5e-3);
  // solver.Solve();


  psolver = &solver;


  cout << "Press  'q'uit   'b'egin  'e'nd  's'tep" << endl;

  int win;

  glutInit(&argc, argv);		/* initialize GLUT system */

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(500,500);		/* width=400pixels height=500pixels */
  win = glutCreateWindow("Hamiltonian");	/* create window */

  /* from this point on the current window is win */
  glClearColor(0.0,0.0,0.0,0.0);	/* set background to black */
  gluOrtho2D(-2, 2, -2, 2);		/* how object is mapped to window */
  glutDisplayFunc(displayCB);		/* set window's display callback */
  glutKeyboardFunc(keyCB);		/* set window's key callback */

  glutIdleFunc (idlefunction);

  glutMainLoop();			/* start processing events... */




  return 0;
}
