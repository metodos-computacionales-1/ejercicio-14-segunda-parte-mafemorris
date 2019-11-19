import numpy as np 
import matplotlib.pylab as plt

xrk4 = np.loadtxt("xrk4.txt")
vrk4 = np.loadtxt("vrk4.txt")
xrk4f = np.loadtxt("xrk4f.txt")
vrk4f = np.loadtxt("vrk4f.txt")
x = np.loadtxt("x.txt")
v = np.loadtxt("v.txt")

plt.figure()
plt.plot(np.linspace(0,20,len(xrk4)),xrk4)
plt.savefig("ondita.png")

plt.figure()
plt.plot(xrk4,vrk4)
plt.savefig("faserk4.png")

plt.figure()
plt.plot(xrk4f,vrk4f)
plt.savefig("faserk4f.png")

plt.figure()
plt.plot(x,v)
plt.savefig("fase.png")