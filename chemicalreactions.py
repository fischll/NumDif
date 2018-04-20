import matplotlib.pyplot as plt1
import matplotlib.pyplot as plt2
s=[]

f = open('build/ChemicalReaction.txt','r')
for line in f:
    line = line.strip()
    s.append([float(x) for x in line.split(' ')])

plt1.semilogy([x[0] for x in s],  [x[1] for x in s],label='Adaptive Step Size')
plt1.grid(True)
plt1.legend()
plt1.show()


for i in range(2,7):
    plt2.semilogy([x[0] for x in s],  [x[i] for x in s],label='dichte ' + str(i))

plt2.grid(True)
plt2.legend()
plt2.show()


