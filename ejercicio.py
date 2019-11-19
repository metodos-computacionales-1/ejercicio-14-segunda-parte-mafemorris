import numpy as np 
import matplotlib.pylab as plt

x = np.loadtxt("x.txt")
v = np.loadtxt("v.txt")

plt.plot(x,v)
plt.savefig("fase.png")