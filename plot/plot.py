import matplotlib.pyplot as plt

#f = open('build/pendulum.txt','r')
#f = open('build/circuit.txt','r')
#f = open('build/diode.txt', 'r')
f = open('build/DifUE_implMP.txt', 'r')
# = open('build/DifUE_explEV.txt', 'r')
h = open('build/DifUE_gauss2.txt', 'r')


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
