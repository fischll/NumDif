import matplotlib.pyplot as plt
import os

#os.system("cd build && make chr")
#os.system("build/chr")


s=[]

f = open('build/satelit.txt','r')
for line in f:
    line = line.strip()
    s.append([float(x) for x in line.split(' ')])

plt.semilogy([x[0] for x in s],  [x[1] for x in s],label='Adaptive Step Size')
plt.grid(True)
plt.legend()
plt.show()

plt.plot([x[2] for x in s],  [x[4] for x in s],label='Kleeblatt')
plt.show()

for i in range(2,5):
    plt.semilogy([x[0] for x in s],  [x[i] for x in s],label='dichte ' + str(i))

plt.grid(True)
plt.legend()
plt.show()


