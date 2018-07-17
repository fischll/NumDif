from netgen.geom2d import unit_square
from ngsolve import *

mesh = Mesh(unit_square.GenerateMesh(maxh=0.1))


fes = H1(mesh, order=1, dirichlet="left|bottom")

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
w = u.vec.CreateVector()

Draw (u)

for it in range(20):
    pre.Smooth (u.vec, f.vec)

    
    # just for the error
    r.data = f.vec - a.mat * u.vec
    w.data = pre * r
    err = sqrt (InnerProduct(r,w))
    if err < 1e-12:
        break
    print ("it =", it, "err = ", err)

Redraw()
