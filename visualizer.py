import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np

def read_file(fileobj):
    tokens = [[], []]
    count = 0
    index = 0
    for line in fileobj:
        for token in line.split():
            if token == "break":
                return tokens
            tokens[index].append(float(token))
            count += 1
            index = count%2
    return tokens
    
file = open(file=r"C:\C++Workspace\QM-1D-Particle\particledata.txt", mode="r")
dt = float(file.readline())
steps = int(file.readline())
dx = float(file.readline())
n = int(file.readline())
psi_data = [[],[]]

for _ in range(steps):
    file_data = read_file(file)
    psi_data[0].append(file_data[0])
    psi_data[1].append(file_data[1])

file.close()

X = np.arange(-n*dx/2, n*dx/2, dx)

fig, ax = plt.subplots()
ax.set_xlabel("x")
ax.set_ylabel("P(Ψ)")
ax.set_xlim(-2,2)
ax.set_ylim(-2,2)

lr, = ax.plot([],[], label="Ψ Re")
li, = ax.plot([],[], label="Ψ Im")
ax.legend()

def anim(frame):
    lr.set_data(X, psi_data[0][frame])
    li.set_data(X, psi_data[1][frame])
    return lr,li,

an = FuncAnimation(fig, anim, steps, interval=1, blit=True)
plt.show()
