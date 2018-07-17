from netgen.geom2d import unit_square
from ngsolve import *

mesh = Mesh(unit_square.GenerateMesh(maxh=0.1))


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
p = u.vec.CreateVector()
ap = u.vec.CreateVector()

Draw (u)

r.data =f.vec - a.mat * u.vec
for it in range(5000):
    #r.data =f.vec - a.mat * u.vec
    p.data = pre * r
    err2 = InnerProduct (p,r)
    if err2 < 1e-6**2:
        break
    ap.data = a.mat * p
    tau = err2/InnerProduct(ap,p)
    print ("it = ", it, "err =", sqrt(err2), ", tau = ", tau)
    u.vec.data += tau * p
    r.data -= tau*ap

Redraw()
