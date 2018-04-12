import matplotlib.pyplot as plt
from numpy import cos

f = open('pendulum.out','r')
H = lambda x,y: -cos(x) + 0.5 * y * y

t, x, y  = [],[],[]

for line in f:
    line = line.strip()
    tn,xn,yn = (float(val) for val in line.split(' '))
    t.append(tn)
    x.append(xn)
    y.append(yn)

f, (ax1, ax2, ax3) = plt.subplots(1, 3)
ax1.plot(t,x)
ax2.plot(x,y)
ax3.plot(t,[H(xn,yn) for xn,yn in zip(x,y)])
plt.show()
