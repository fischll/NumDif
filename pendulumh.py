import matplotlib.pyplot as plt



s=[]

f = open('build/pendulumh.txt','r')

for line in f:
    line = line.strip()
    s.append([float(x) for x in line.split(' ')])

plt.figure(1)
plt.subplot(1,2,1)
plt.plot([x[1] for x in s],  [x[2] for x in s],label='Ort')
plt.grid(True)

plt.subplot(1,2,2)
plt.plot([x[0] for x in s],  [x[3] for x in s],label='Energie')

plt.legend()

plt.figure(2)
plt.plot([x[0] for x in s],  [x[3] for x in s],label='Energie')

plt.figure(3)
plt.subplot(2,1,1)
plt.plot([x[0] for x in s],  [x[1] for x in s],label='Winkelgeschwindigkeit')
plt.grid(True)
plt.legend()

plt.subplot(2,1,2)
plt.plot([x[0] for x in s],  [x[2] for x in s],label='Winkelort')

plt.grid(True)
plt.legend()
plt.show()


