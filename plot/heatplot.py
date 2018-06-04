import matplotlib.pyplot as plt
import math

data = open('../build/heateqn.txt', 'r')

##############################
def ExactSolution(x):
    if x < 0.5:
        return -x*x/20 + x*111/440
    else:
        return -x*x/2 + x*111/44 - 45/44
##############################

s=[]
for line in data:
    line = line.strip()
    s.append([float(x) for x in line.split(' ')])


plt.plot([x[0] for x in s], [x[1] for x in s], label='u')
plt.legend()
plt.show()

plt.plot([x[0] for x in s], [x[2] for x in s], label='Diskreter Waermefluss')
plt.legend()
plt.show()

plt.plot([x[0] for x in s],[ExactSolution(x[0])-x[1] for x in s], label = "Error")
plt.legend()
plt.show()
