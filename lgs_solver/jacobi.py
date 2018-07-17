from netgen.geom2d import unit_square
from ngsolve import *

mesh = Mesh(unit_square.GenerateMesh(maxh=0.05))


fes = H1(mesh, order=1, dirichlet="left|bottom")
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
w = u.vec.CreateVector()

Draw (u)

for it in range(5000):
    r.data = f.vec - a.mat * u.vec
    w.data = pre * r
    err = sqrt(InnerProduct (w,r))
    if err < 1e-6:
        break
    print ("it = ", it, "err =", err)
    u.vec.data += 0.8 * w

Redraw()
