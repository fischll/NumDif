

import matplotlib.pyplot as plt
from numpy import *

t, p, q, H = [], [], [], []

with open("bsp26.out","r") as f:
    for line in f:
        tn,pn,qn,Hn = (float(val) for val in line.split(" "))
        t.append(tn)
        p.append(pn)
        q.append(qn)
        H.append(Hn)

f, ((ax1,ax2),(ax3,ax4)) = plt.subplots(2,2)
ax1.plot(t,p)
ax1.set_title("p")
ax2.plot(t,q)
ax2.set_title("q")
ax3.plot(t,H)
ax3.set_title("H")
# ax4.plot(t,h)
plt.show()
