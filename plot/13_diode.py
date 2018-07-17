import matplotlib.pyplot as plt

#f = open('build/pendulum.txt','r')
#f = open('build/circuit.txt','r')
f = open('build/diode.txt', 'r')

s=[]
for line in f:
    line = line.strip()
    s.append([float(x) for x in line.split(' ')])

plt.plot([x[0] for x in s], [x[1] for x in s])
plt.show()
