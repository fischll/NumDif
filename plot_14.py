import matplotlib.pyplot as plt

s=[]

f = open('install/circuit_impl_MP.out','r')
for line in f:
    line = line.strip()
    s.append([float(x) for x in line.split(' ')])
plt.plot([x[0] for x in s], [x[1] for x in s],label='implMP')

#f = open('install/circuit_expl_EV.out','r')
#for line in f:
#    line = line.strip()
#    s.append([float(x) for x in line.split(' ')])
#plt.plot([x[0] for x in s], [x[1] for x in s],label='explEV')

s=[]
f = open('install/circuit_impl_EV.out','r')
for line in f:
    line = line.strip()
    s.append([float(x) for x in line.split(' ')])
plt.plot([x[0] for x in s], [x[1] for x in s],label='implEV')


s=[]
f = open('install/circuit_bsp16.out','r')
for line in f:
    line = line.strip()
    s.append([float(x) for x in line.split(' ')])
plt.plot([x[0] for x in s], [x[1] for x in s],label='bsp16')

plt.legend()

plt.show()
