import matplotlib.pyplot as plt
import numpy as np

def read_file(fileobj):
    tokens = [[], []]
    count = 0
    index = 0
    for line in fileobj:
        for token in line.split():
            tokens[index].append(float(token))
            count += 1
            index = count%2
    
    return tokens

file = open(file=r"particledata.txt", mode="r")
psi_data = read_file(file)

# Create domain to visualize the data
# TODO: write domain from main.cpp to particledata.txt
X = np.arange(-10, 10, 0.01)

fig, ax = plt.subplots()
ax.set_xlabel("x")
ax.set_ylabel("P(Ψ)")
ax.set_title(f"Steps: {len(psi_data[0])//2}")
ax.plot(X, psi_data[0], label="Ψ Re")
ax.plot(X, psi_data[1], label="Ψ Im")
ax.legend()
plt.show()
