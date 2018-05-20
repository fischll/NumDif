import matplotlib.pyplot as plt

f = open('../build/heateqn.txt', 'r')

s=[]
for line in f:
    line = line.strip()
    s.append([float(x) for x in line.split(' ')])

plt.plot([x[0] for x in s], [x[1] for x in s], label='u')
plt.legend()
plt.show()