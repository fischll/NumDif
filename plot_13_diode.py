import matplotlib.pyplot as plt

#f = open('install/pendulum.out','r')
#f = open('install/circuit.out','r')
f = open('install/diode.out', 'r')

s=[]
for line in f:
    line = line.strip()
    s.append([float(x) for x in line.split(' ')])

plt.plot([x[0] for x in s], [x[1] for x in s])
plt.show()
