import matplotlib.pyplot as plt
import os

#os.system("cd build && cmake ..")
#os.system("make -C ./build -j satelit")
#os.system("cd build/satelit")


s=[]

f = open('build/satelit.txt','r')
for line in f:
    line = line.strip()
    s.append([float(x) for x in line.split(' ')])

for x in s:
     x[2] = x[2]*384000
     x[4] = x[4]*384000

plt.figure(1)
plt.plot([x[2] for x in s],  [x[4] for x in s],label='Kleeblatt')

plt.figure(2)
plt.subplot(2,1,1)
plt.semilogy([x[0] for x in s],  [x[1] for x in s],label='Adaptive Step Size')
plt.grid(True)
plt.legend()

plt.subplot(2,1,2)
#for i in range(2,5):
#    plt.plot([x[0] for x in s],  [x[i] for x in s],label='dichte ' + str(i))
plt.plot([x[0] for x in s],  [x[3] for x in s],label='Kleeblatt')

plt.grid(True)
plt.legend()
plt.show()


