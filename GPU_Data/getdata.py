import numpy as np
import matplotlib.pyplot as plt
np.set_printoptions(threshold=10000000)
rand = np.random.RandomState(42)
n = 100000
t = n * rand.rand(n)
y = np.sin(2 * np.pi * t) + 0.1 * rand.randn(n)



f = open("./GPU_Data/cyclic-data.hpp","w")
f.write("double input_data[] = {" + np.array2string(y,separator=',')[1:-1] + "};\n\n")
f.write("double times[] = {" + np.array2string(t,separator=',')[1:-1] + "};\n\n")
f.write("double frequencies[] = {" + np.array2string(np.linspace(0,2.5,10*n),separator=',')[1:-1] + "};")
f.close()
