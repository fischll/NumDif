import matplotlib.pyplot as plt
import numpy as np
import math
##############################
#def chebyshev1(x,m):
#        return math.pow((-1.0),m)*math.cosh(m*math.acosh(x))
#def chebyshev2(x,m):
#        return math.cos(m*math.acos(x))
#def chebyshev3(x,m):
#        return math.cosh(m*math.acosh(x))
##############################
###############################
#for m in range(1,10):
#    x = np.arange(-2.0, -1.0, 0.01)
#    plt.plot(x, chebyshev1(x,m))
#    x = np.arange(-1.0, 1.0, 0.01)
#    plt.plot(x, chebyshev2(x,m))
#    x = np.arange(1.0, 2.0, 0.01)
#    plt.plot(x, chebyshev3(x,m))
#plt.grid(True)
#plt.ylim((-2,2))
#plt.show()

##################################################
def rekursiv(x,m):
    if m==0:
        return 1
    elif m==1:
        return x
    else:
        return 2*x*rekursiv(x,m-1) - rekursiv(x,m-2)
##################################################
def q(x,m,a,b):
    return rekursiv((2*x - a - b)/(b - a),m)/rekursiv((-a - b)/(b - a) ,m)
##################################################
plt.figure(1)
for m in range(1,10):
    x = np.arange(-2.0, 2.0, 0.01)
    plt.plot(x, rekursiv(x,m))
plt.grid(True)
plt.ylim((-2,2))

plt.figure(2)
a = 0.05
b = 1
for m in [5,10,20]:
    y = np.arange(0.05, 1.0, 0.002)
    plt.plot(y, q(y,m,a,b))
plt.grid(True)
plt.show()

