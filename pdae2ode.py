import matplotlib.pyplot as plt


s=[]

f = open('build/PenDAE2ODE.txt','r')

for line in f:
    line = line.strip()
    s.append([float(x) for x in line.split(' ')])

plt.figure(1)
plt.subplot(1,2,1)
plt.plot([x[3] for x in s],  [x[4] for x in s],label='Ort')
plt.grid(True)

plt.subplot(1,2,2)
plt.plot([x[1] for x in s],  [x[2] for x in s],label='Geschwindigkeit')

plt.figure(2)
plt.subplot(1,2,1)
plt.plot([x[0] for x in s],  [x[1] for x in s],label='geschw. zu Zeit')
plt.grid(True)

plt.subplot(1,2,2)
plt.plot([x[0] for x in s],  [x[3] for x in s],label='geschw. zu Zeit')
plt.legend()


plt.figure(3)
plt.plot([x[0] for x in s], [x[1]*x[1]/2+x[2]*x[2]/2 + x[4] for x in s],label='Energy')
plt.grid(True)
plt.legend()
plt.show()


