import matplotlib.pyplot as plt


f = open('build/Pen_implMP.txt', 'r')
s=[]
for line in f:
    line = line.strip()
    s.append([float(x) for x in line.split(' ')])
plt.plot([x[1] for x in s], [x[2] for x in s],label='implMP')

f = open('build/Pen_gauss2.txt', 'r')
s=[]
for line in f:
    line = line.strip()
    s.append([float(x) for x in line.split(' ')])
plt.plot([x[1] for x in s], [x[2] for x in s],label='gauss2')
plt.legend()
plt.show()
