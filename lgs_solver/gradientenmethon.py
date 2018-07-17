from netgen.geom2d import unit_square
from netgen.csg import unit_cube
from ngsolve import *
from time import time

mesh = Mesh(unit_square.GenerateMesh(maxh=0.1))
# mesh = Mesh(unit_cube.GenerateMesh(maxh=0.1))

fes = H1(mesh, order=1, dirichlet="left|bottom|front")
print ("ndof =", fes.ndof)

u,v = fes.TnT()

a = BilinearForm(fes)
a += SymbolicBFI(grad(u)*grad(v))
a.Assemble()

f = LinearForm(fes)
f += SymbolicLFI(1 * v)
f.Assemble()

u = GridFunction(fes)

pre = a.mat.CreateSmoother(fes.FreeDofs())

r = u.vec.CreateVector()
p = u.vec.CreateVector()
ap = u.vec.CreateVector()

Draw (u)

start = time()

method = "cg"
# method = "gradient"

print ("start solver")
if method == "cg":
    solvers.CG (mat = a.mat, pre=pre, rhs = f.vec, sol=u.vec, maxsteps=1000)

if method == "gradient":
    r.data = f.vec - a.mat * u.vec
    for it in range(5000):
        p.data = pre * r
        err2 = InnerProduct (p,r)
        if err2 < 1e-20**2:
            break
        ap.data = a.mat * p
        tau = err2 / InnerProduct (ap, p)
        print ("it = ", it, "err =", sqrt(err2), ", tau = ", tau)
        u.vec.data += tau * p
        r.data -= tau * ap
    
    
Redraw()
print ("time = ", time()-start)
