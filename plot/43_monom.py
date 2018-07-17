import matplotlib.pyplot as plt

f = open('../build/monombasis.txt', 'r')

s=[]
for line in f:
    line = line.strip()
    s.append([float(x) for x in line.split(' ')])


plt.plot([x[0] for x in s], [x[1] for x in s], label='u_p-fem')

plt.plot([x[0] for x in s], [x[2] for x in s], label='u_analytisch')
plt.legend()
plt.show()
