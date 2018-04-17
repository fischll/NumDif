import matplotlib.pyplot as plt

s=[]

f = open('install/ChemicalReaction.out','r')
for line in f:
    line = line.strip()
    s.append([float(x) for x in line.split(' ')])
plt.plot([x[0] for x in s], [x[1] for x in s],label='h')

plt.legend()

plt.show()

