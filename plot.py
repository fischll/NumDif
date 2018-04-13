import matplotlib.pyplot as plt

#f = open('install/pendulum.out','r')
#f = open('install/circuit.out','r')
#f = open('install/diode.out', 'r')
f = open('install/DifUE_implMP.out', 'r')
# = open('install/DifUE_explEV.out', 'r')
h = open('install/DifUE_gauss2.out', 'r')


s=[]
#for line in f:
#    line = line.strip()
#    s.append([float(x) for x in line.split(' ')])

#plt.plot([x[0] for x in s], [x[1] for x in s],label='implMP')

#for line in g:
#    line = line.strip()
#    s.append([float(x) for x in line.split(' ')])

#plt.plot([x[0] for x in s], [x[1] for x in s],label='explEV')

for line in h:
    line = line.strip()
    s.append([float(x) for x in line.split(' ')])

plt.plot([x[0] for x in s], [x[1] for x in s],label='gauss2')

plt.legend()
plt.show()
