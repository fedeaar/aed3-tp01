import numpy as np

np.random.seed(11037)

for power in range(16,27):
    n = 2 ** power
    f = open("inputs/input_" + str(n), "w")
    for i in n:
        s = np.random.randint(0,2*n)
        f.write(str(s) + " " + str(np.random.randint(s+1,2*n+1)) + " ")
    f.close()
