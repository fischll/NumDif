
from netgen.geom2d import SplineGeometry, MakeRectangle, MakeCircle
from ngsolve import *

geo = SplineGeometry()

#MakeRectangle(geo, (0,0), (4,4), bc="outer")
#MakeRectangle(geo, (2,2),(3,3), leftdomain=2, rightdomain=1)
MakeRectangle(geo, (0,0), (1,1), bc="outer")

ngmesh = geo.GenerateMesh(maxh=0.02)
ngmesh.SetMaterial(1,"water")
#ngmesh.SetMaterial(1,"air")
#ngmesh.SetMaterial(2,"source")
mesh = Mesh(ngmesh)

Draw(mesh)

t = 0
tend = 10
dt = 1e-4

fes = H1(mesh, order=0, neumann="outer") #order=3
u, test_func = fes.TnT()

M_stern = BilinearForm(fes)
#M_stern += SymbolicBFI(u*test_func + dt * grad(u) * grad(test_func))
M_stern += SymbolicBFI(u*test_func +  dt*dt/4*grad(u)*grad(test_func))

A = BilinearForm(fes)
A += SymbolicBFI(grad(u)*grad(test_func))

#cf = Parameter(1)

f = LinearForm(fes)
#f += SymbolicLFI(cf * test_func, definedon=mesh.Materials("source"))


u = GridFunction(fes)
u.Set(exp(-20*20*((x-0.5)*(x-0.5) + (y-0.2)*(y-0.2))))



Draw(u)

M_stern.Assemble()
inv = M_stern.mat.Inverse(fes.FreeDofs())

A.Assemble()

r = u.vec.CreateVector()
r[:] = 0.0
v = u.vec.CreateVector()
v[:] = 0.0
dv = u.vec.CreateVector()
dv[:] = 0.0
input("press key to start...")

while t < tend:
    t += dt
    print("\rt = ",t, end="")
    #cf.Set(10*int(t > 2))
    #f.Assemble()
    r.data =  - dt*A.mat*u.vec - dt*dt/2*A.mat*v #A.mat * u.vec + dt * f.vec
    dv.data = inv*r
    u.vec.data += dt/2*(2*v + dv)
    v.data += dv
    Redraw(blocking=True)

